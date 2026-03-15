#include "DistortionSection.h"
#include "../ParameterIDs.h"
#include "ErinSynthLookAndFeel.h"

DistortionSection::DistortionSection (juce::AudioProcessorValueTreeState& apvts)
{
    addAndMakeVisible (enabledButton);
    enabledAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment> (
        apvts, ParamIDs::distortionEnabled, enabledButton);

    typeBox.addItemList ({ "Soft Clip", "Hard Clip", "Foldback", "Bitcrush", "Waveshape" }, 1);
    addAndMakeVisible (typeBox);
    typeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment> (
        apvts, ParamIDs::distortionType, typeBox);

    typeLabel.setText ("Type", juce::dontSendNotification);
    typeLabel.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (typeLabel);

    driveSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    driveSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 50, 16);
    addAndMakeVisible (driveSlider);
    driveAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        apvts, ParamIDs::distortionDrive, driveSlider);
    driveLabel.setText ("Drive", juce::dontSendNotification);
    driveLabel.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (driveLabel);

    mixSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    mixSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 50, 16);
    addAndMakeVisible (mixSlider);
    mixAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        apvts, ParamIDs::distortionMix, mixSlider);
    mixLabel.setText ("Mix", juce::dontSendNotification);
    mixLabel.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (mixLabel);
}

void DistortionSection::paint (juce::Graphics& g)
{
    g.setColour (ErinSynthLookAndFeel::panelColour);
    g.fillRoundedRectangle (getLocalBounds().toFloat(), 6.0f);

    g.setColour (ErinSynthLookAndFeel::accentColour);
    g.drawRoundedRectangle (getLocalBounds().toFloat().reduced (1.0f), 6.0f, 1.0f);

    g.setColour (ErinSynthLookAndFeel::textColour);
    g.setFont (14.0f);
    g.drawText ("DISTORTION", getLocalBounds().removeFromTop (25), juce::Justification::centred);
}

void DistortionSection::resized()
{
    auto bounds = getLocalBounds().reduced (10);
    bounds.removeFromTop (25);

    // Top row: enable toggle + type selector
    auto topRow = bounds.removeFromTop (28);
    enabledButton.setBounds (topRow.removeFromLeft (50));
    topRow.removeFromLeft (6);
    typeLabel.setBounds (topRow.removeFromLeft (40));
    typeBox.setBounds (topRow);

    bounds.removeFromTop (8);

    // Bottom row: drive and mix knobs
    int knobWidth = bounds.getWidth() / 2;

    auto driveArea = bounds.removeFromLeft (knobWidth);
    driveLabel.setBounds (driveArea.removeFromTop (18));
    driveSlider.setBounds (driveArea);

    auto mixArea = bounds;
    mixLabel.setBounds (mixArea.removeFromTop (18));
    mixSlider.setBounds (mixArea);
}
