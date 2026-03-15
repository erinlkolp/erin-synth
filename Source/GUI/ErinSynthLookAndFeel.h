#pragma once
#include <JuceHeader.h>

class ErinSynthLookAndFeel : public juce::LookAndFeel_V4
{
public:
    ErinSynthLookAndFeel();

    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height,
                           float sliderPosProportional, float rotaryStartAngle,
                           float rotaryEndAngle, juce::Slider& slider) override;

    static const juce::Colour backgroundColour;
    static const juce::Colour panelColour;
    static const juce::Colour accentColour;
    static const juce::Colour meterGreen;
    static const juce::Colour meterYellow;
    static const juce::Colour meterRed;
    static const juce::Colour textColour;
};
