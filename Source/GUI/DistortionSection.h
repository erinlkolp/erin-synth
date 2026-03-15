#pragma once
#include <JuceHeader.h>

class DistortionSection : public juce::Component
{
public:
    DistortionSection (juce::AudioProcessorValueTreeState& apvts);
    void resized() override;
    void paint (juce::Graphics& g) override;

private:
    juce::ToggleButton enabledButton { "On" };
    juce::ComboBox typeBox;
    juce::Slider driveSlider, mixSlider;
    juce::Label typeLabel, driveLabel, mixLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> enabledAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> typeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> driveAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mixAttachment;
};
