#pragma once
#include <JuceHeader.h>

class FilterEnvSection : public juce::Component
{
public:
    FilterEnvSection (juce::AudioProcessorValueTreeState& apvts);
    void resized() override;
    void paint (juce::Graphics& g) override;

private:
    juce::Slider depthSlider, attackSlider, decaySlider, sustainSlider, releaseSlider;
    juce::Label  depthLabel,  attackLabel,  decayLabel,  sustainLabel,  releaseLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> depthAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> decayAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sustainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> releaseAttachment;

    void setupSlider (juce::Slider& slider, juce::Label& label, const juce::String& text);
};
