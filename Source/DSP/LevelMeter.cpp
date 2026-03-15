#include "LevelMeter.h"

void LevelMeter::prepare (double sampleRate)
{
    // Attack: ~10ms, Release: ~300ms
    float attackTimeMs  = 10.0f;
    float releaseTimeMs = 300.0f;

    attackCoeff  = 1.0f - std::exp (-1.0f / (static_cast<float> (sampleRate) * attackTimeMs  * 0.001f));
    releaseCoeff = 1.0f - std::exp (-1.0f / (static_cast<float> (sampleRate) * releaseTimeMs * 0.001f));

    reset();
}

void LevelMeter::reset()
{
    smoothedLeft  = 0.0f;
    smoothedRight = 0.0f;
    levelLeft.store (-100.0f, std::memory_order_relaxed);
    levelRight.store (-100.0f, std::memory_order_relaxed);
}

void LevelMeter::measureBlock (const juce::AudioBuffer<float>& buffer)
{
    auto processChannel = [] (const float* data, int numSamples, float& smoothed,
                              float attack, float release) -> float
    {
        for (int i = 0; i < numSamples; ++i)
        {
            float absVal = std::abs (data[i]);
            float coeff = absVal > smoothed ? attack : release;
            smoothed += coeff * (absVal - smoothed);
        }

        return smoothed > 1e-6f
                   ? juce::Decibels::gainToDecibels (smoothed)
                   : -100.0f;
    };

    int numSamples = buffer.getNumSamples();

    if (buffer.getNumChannels() > 0)
    {
        float dbLeft = processChannel (buffer.getReadPointer (0), numSamples,
                                       smoothedLeft, attackCoeff, releaseCoeff);
        levelLeft.store (dbLeft, std::memory_order_relaxed);
    }

    if (buffer.getNumChannels() > 1)
    {
        float dbRight = processChannel (buffer.getReadPointer (1), numSamples,
                                        smoothedRight, attackCoeff, releaseCoeff);
        levelRight.store (dbRight, std::memory_order_relaxed);
    }
    else
    {
        levelRight.store (levelLeft.load (std::memory_order_relaxed), std::memory_order_relaxed);
    }
}
