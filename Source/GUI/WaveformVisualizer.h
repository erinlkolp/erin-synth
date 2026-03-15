#pragma once
#include <JuceHeader.h>
#include "../DSP/WaveformBuffer.h"
#include "ErinSynthLookAndFeel.h"

class WaveformVisualizer : public juce::Component, private juce::Timer
{
public:
    WaveformVisualizer (WaveformBuffer& buffer);
    ~WaveformVisualizer() override;

    void paint (juce::Graphics& g) override;
    void resized() override {}

private:
    void timerCallback() override;

    WaveformBuffer& waveformSource;
    std::vector<float> displayBuffer;
    static constexpr int displaySize = 512;
};
