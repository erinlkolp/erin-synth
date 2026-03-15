#pragma once
#include <JuceHeader.h>

class LevelMeter
{
public:
    void prepare (double sampleRate);
    void reset();
    void measureBlock (const juce::AudioBuffer<float>& buffer);

    float getLevelLeft() const  { return levelLeft.load (std::memory_order_relaxed); }
    float getLevelRight() const { return levelRight.load (std::memory_order_relaxed); }

private:
    std::atomic<float> levelLeft { -100.0f };
    std::atomic<float> levelRight { -100.0f };

    float smoothedLeft = 0.0f;
    float smoothedRight = 0.0f;

    float attackCoeff = 0.0f;
    float releaseCoeff = 0.0f;
};
