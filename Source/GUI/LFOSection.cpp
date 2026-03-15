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

    depthSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    depthSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 44, 14);
    addAndMakeVisible (depthSlider);
    depthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        apvts, ParamIDs::lfoDepth, depthSlider);

    depthLabel.setText ("Depth", juce::dontSendNotification);
    depthLabel.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (depthLabel);
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

    int knobW = bounds.getWidth() / 2;

    auto leftKnob = bounds.removeFromLeft (knobW);
    rateLabel.setBounds (leftKnob.removeFromTop (14));
    rateSlider.setBounds (leftKnob);

    depthLabel.setBounds (bounds.removeFromTop (14));
    depthSlider.setBounds (bounds);
}
