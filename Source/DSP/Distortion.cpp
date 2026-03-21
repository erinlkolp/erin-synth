#include "Distortion.h"

void Distortion::prepare (const juce::dsp::ProcessSpec&)
{
    reset();
}

void Distortion::reset()
{
}

float Distortion::processSample (float input) const
{
    float driven = input * driveLinear;

    switch (currentType)
    {
        case SoftClip:
            return std::tanh (driven);

        case HardClip:
            return juce::jlimit (-1.0f, 1.0f, driven);

        case Foldback:
        {
            // O(1) foldback via triangle wave math (replaces iterative loop)
            float phase = (driven + 1.0f) * 0.5f;
            phase = std::fmod (phase, 2.0f);
            if (phase < 0.0f) phase += 2.0f;
            float folded = (phase <= 1.0f) ? phase : 2.0f - phase;
            return folded * 2.0f - 1.0f;
        }

        case Bitcrush:
        {
            // Map drive (1.0 = 0dB to ~100 = 40dB) to bit depth (16 down to 2)
            float bitDepth = juce::jmap (driveLinear, 1.0f, 100.0f, 16.0f, 2.0f);
            bitDepth = juce::jlimit (2.0f, 16.0f, bitDepth);
            float levels = std::pow (2.0f, bitDepth);
            return juce::jlimit (-1.0f, 1.0f, std::round (driven * levels) / levels);
        }

        case Waveshape:
        {
            // Soft cubic waveshaper
            float x = driven;
            return juce::jlimit (-1.0f, 1.0f, x * (27.0f + x * x) / (27.0f + 9.0f * x * x));
        }

        default:
            return input;
    }
}

void Distortion::process (juce::AudioBuffer<float>& buffer)
{
    if (! enabled)
        return;

    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        float* data = buffer.getWritePointer (channel);
        int numSamples = buffer.getNumSamples();

        for (int i = 0; i < numSamples; ++i)
        {
            float dry = data[i];
            float wet = processSample (dry);
            data[i] = dry + mixProportion * (wet - dry);
        }
    }
}
