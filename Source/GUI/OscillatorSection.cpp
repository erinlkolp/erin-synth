#include "OscillatorSection.h"
#include "../ParameterIDs.h"
#include "ErinSynthLookAndFeel.h"

OscillatorSection::OscillatorSection (juce::AudioProcessorValueTreeState& apvts)
{
    // OSC 1 waveform
    waveformBox.addItemList ({ "Sine", "Saw", "Square", "Triangle", "Noise" }, 1);
    addAndMakeVisible (waveformBox);
    waveformAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment> (
        apvts, ParamIDs::oscWaveform, waveformBox);

    waveformLabel.setText ("OSC 1", juce::dontSendNotification);
    waveformLabel.setJustificationType (juce::Justification::centredLeft);
    addAndMakeVisible (waveformLabel);

    // OSC 1 level
    osc1LevelSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    osc1LevelSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 44, 14);
    addAndMakeVisible (osc1LevelSlider);
    osc1LevelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        apvts, ParamIDs::osc1Level, osc1LevelSlider);

    osc1LevelLabel.setText ("Level", juce::dontSendNotification);
    osc1LevelLabel.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (osc1LevelLabel);

    // OSC 2 waveform
    osc2WaveformBox.addItemList ({ "Sine", "Saw", "Square", "Triangle", "Noise" }, 1);
    addAndMakeVisible (osc2WaveformBox);
    osc2WaveformAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment> (
        apvts, ParamIDs::osc2Waveform, osc2WaveformBox);

    osc2WaveformLabel.setText ("OSC 2", juce::dontSendNotification);
    osc2WaveformLabel.setJustificationType (juce::Justification::centredLeft);
    addAndMakeVisible (osc2WaveformLabel);

    // OSC 2 level
    osc2LevelSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    osc2LevelSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 44, 14);
    addAndMakeVisible (osc2LevelSlider);
    osc2LevelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        apvts, ParamIDs::osc2Level, osc2LevelSlider);

    osc2LevelLabel.setText ("Level", juce::dontSendNotification);
    osc2LevelLabel.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (osc2LevelLabel);

    // Sub oscillator level
    subOscLevelSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    subOscLevelSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 44, 14);
    addAndMakeVisible (subOscLevelSlider);
    subOscLevelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        apvts, ParamIDs::subOscLevel, subOscLevelSlider);

    subOscLevelLabel.setText ("SUB", juce::dontSendNotification);
    subOscLevelLabel.setJustificationType (juce::Justification::centredLeft);
    addAndMakeVisible (subOscLevelLabel);
}

void OscillatorSection::paint (juce::Graphics& g)
{
    g.setColour (ErinSynthLookAndFeel::panelColour);
    g.fillRoundedRectangle (getLocalBounds().toFloat(), 6.0f);

    g.setColour (ErinSynthLookAndFeel::accentColour);
    g.drawRoundedRectangle (getLocalBounds().toFloat().reduced (1.0f), 6.0f, 1.0f);

    g.setColour (ErinSynthLookAndFeel::textColour);
    g.setFont (14.0f);
    g.drawText ("OSCILLATORS", getLocalBounds().removeFromTop (25), juce::Justification::centred);
}

void OscillatorSection::resized()
{
    auto bounds = getLocalBounds().reduced (10);
    bounds.removeFromTop (25); // title

    int rowHeight = bounds.getHeight() / 3;
    int knobSize = rowHeight - 4;

    // OSC 1 row
    auto row1 = bounds.removeFromTop (rowHeight);
    auto knob1Area = row1.removeFromRight (knobSize + 10);
    osc1LevelLabel.setBounds (knob1Area.removeFromTop (14));
    osc1LevelSlider.setBounds (knob1Area);
    waveformLabel.setBounds (row1.removeFromTop (18));
    row1.removeFromTop (2);
    waveformBox.setBounds (row1.removeFromTop (24));

    // OSC 2 row
    auto row2 = bounds.removeFromTop (rowHeight);
    auto knob2Area = row2.removeFromRight (knobSize + 10);
    osc2LevelLabel.setBounds (knob2Area.removeFromTop (14));
    osc2LevelSlider.setBounds (knob2Area);
    osc2WaveformLabel.setBounds (row2.removeFromTop (18));
    row2.removeFromTop (2);
    osc2WaveformBox.setBounds (row2.removeFromTop (24));

    // Sub row
    auto row3 = bounds;
    auto knob3Area = row3.removeFromRight (knobSize + 10);
    subOscLevelLabel.setBounds (row3.removeFromTop (18));
    subOscLevelSlider.setBounds (knob3Area);
}
