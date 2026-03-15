#pragma once
#include <JuceHeader.h>

class LFOSection : public juce::Component
{
public:
    LFOSection (juce::AudioProcessorValueTreeState& apvts);
    void resized() override;
    void paint (juce::Graphics& g) override;

private:
    juce::Slider rateSlider;
    juce::Label rateLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> rateAttachment;

    juce::Slider filterDepthSlider;
    juce::Label filterDepthLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterDepthAttachment;

    juce::Slider pitchDepthSlider;
    juce::Label pitchDepthLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> pitchDepthAttachment;
};
