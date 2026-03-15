#pragma once
#include <JuceHeader.h>

class GainSection : public juce::Component
{
public:
    GainSection (juce::AudioProcessorValueTreeState& apvts);
    void resized() override;
    void paint (juce::Graphics& g) override;

private:
    juce::Slider gainSlider;
    juce::Label gainLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
};
