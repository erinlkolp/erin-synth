#include "LFOSection.h"
#include "../ParameterIDs.h"
#include "ErinSynthLookAndFeel.h"

LFOSection::LFOSection (juce::AudioProcessorValueTreeState& apvts)
{
    rateSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    rateSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 50, 14);
    rateSlider.setTextValueSuffix (" Hz");
    addAndMakeVisible (rateSlider);
    rateAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        apvts, ParamIDs::lfoRate, rateSlider);

    rateLabel.setText ("Rate", juce::dontSendNotification);
    rateLabel.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (rateLabel);

    filterDepthSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    filterDepthSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 44, 14);
    addAndMakeVisible (filterDepthSlider);
    filterDepthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        apvts, ParamIDs::lfoDepth, filterDepthSlider);

    filterDepthLabel.setText ("Filter", juce::dontSendNotification);
    filterDepthLabel.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (filterDepthLabel);

    pitchDepthSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    pitchDepthSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 44, 14);
    addAndMakeVisible (pitchDepthSlider);
    pitchDepthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        apvts, ParamIDs::lfoPitchDepth, pitchDepthSlider);

    pitchDepthLabel.setText ("Pitch", juce::dontSendNotification);
    pitchDepthLabel.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (pitchDepthLabel);
}

void LFOSection::paint (juce::Graphics& g)
{
    g.setColour (ErinSynthLookAndFeel::panelColour);
    g.fillRoundedRectangle (getLocalBounds().toFloat(), 6.0f);

    g.setColour (ErinSynthLookAndFeel::accentColour);
    g.drawRoundedRectangle (getLocalBounds().toFloat().reduced (1.0f), 6.0f, 1.0f);

    g.setColour (ErinSynthLookAndFeel::textColour);
    g.setFont (14.0f);
    g.drawText ("LFO", getLocalBounds().removeFromTop (25), juce::Justification::centred);
}

void LFOSection::resized()
{
    auto bounds = getLocalBounds().reduced (10);
    bounds.removeFromTop (25);

    int knobW = bounds.getWidth() / 3;

    auto rateArea = bounds.removeFromLeft (knobW);
    rateLabel.setBounds (rateArea.removeFromTop (14));
    rateSlider.setBounds (rateArea);

    auto filterArea = bounds.removeFromLeft (knobW);
    filterDepthLabel.setBounds (filterArea.removeFromTop (14));
    filterDepthSlider.setBounds (filterArea);

    pitchDepthLabel.setBounds (bounds.removeFromTop (14));
    pitchDepthSlider.setBounds (bounds);
}
