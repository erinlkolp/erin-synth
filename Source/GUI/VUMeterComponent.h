#pragma once
#include <JuceHeader.h>
#include "../DSP/LevelMeter.h"
#include "ErinSynthLookAndFeel.h"

class VUMeterComponent : public juce::Component, private juce::Timer
{
public:
    VUMeterComponent (LevelMeter& meter, const juce::String& label);
    ~VUMeterComponent() override;

    void paint (juce::Graphics& g) override;
    void resized() override {}

private:
    void timerCallback() override;
    void drawMeterBar (juce::Graphics& g, juce::Rectangle<float> bounds, float levelDb);

    LevelMeter& meterSource;
    juce::String meterLabel;
    float currentLeftDb  = -100.0f;
    float currentRightDb = -100.0f;
};
