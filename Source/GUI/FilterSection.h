#pragma once
#include <JuceHeader.h>

class FilterSection : public juce::Component
{
public:
    FilterSection (juce::AudioProcessorValueTreeState& apvts);
    void resized() override;
    void paint (juce::Graphics& g) override;

private:
    juce::ComboBox typeBox;
    juce::Label typeLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> typeAttachment;

    juce::Slider cutoffSlider;
    juce::Label cutoffLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> cutoffAttachment;

    juce::Slider resonanceSlider;
    juce::Label resonanceLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> resonanceAttachment;
};
