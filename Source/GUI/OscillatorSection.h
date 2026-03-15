#pragma once
#include <JuceHeader.h>

class OscillatorSection : public juce::Component
{
public:
    OscillatorSection (juce::AudioProcessorValueTreeState& apvts);
    void resized() override;
    void paint (juce::Graphics& g) override;

private:
    // OSC 1
    juce::ComboBox waveformBox;
    juce::Label waveformLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> waveformAttachment;

    juce::Slider osc1LevelSlider;
    juce::Label osc1LevelLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> osc1LevelAttachment;

    // OSC 2
    juce::ComboBox osc2WaveformBox;
    juce::Label osc2WaveformLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> osc2WaveformAttachment;

    juce::Slider osc2LevelSlider;
    juce::Label osc2LevelLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> osc2LevelAttachment;

    // Sub
    juce::Slider subOscLevelSlider;
    juce::Label subOscLevelLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> subOscLevelAttachment;
};
