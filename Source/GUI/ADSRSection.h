#pragma once
#include <JuceHeader.h>

class ADSRSection : public juce::Component
{
public:
    ADSRSection (juce::AudioProcessorValueTreeState& apvts);
    void resized() override;
    void paint (juce::Graphics& g) override;

private:
    juce::Slider attackSlider, decaySlider, sustainSlider, releaseSlider;
    juce::Label attackLabel, decayLabel, sustainLabel, releaseLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> decayAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sustainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> releaseAttachment;

    void setupSlider (juce::Slider& slider, juce::Label& label, const juce::String& text);
};
