#include "ADSRSection.h"
#include "../ParameterIDs.h"
#include "ErinSynthLookAndFeel.h"

ADSRSection::ADSRSection (juce::AudioProcessorValueTreeState& apvts)
{
    setupSlider (attackSlider,  attackLabel,  "A");
    setupSlider (decaySlider,   decayLabel,   "D");
    setupSlider (sustainSlider, sustainLabel, "S");
    setupSlider (releaseSlider, releaseLabel, "R");

    attackAttachment  = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        apvts, ParamIDs::attack, attackSlider);
    decayAttachment   = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        apvts, ParamIDs::decay, decaySlider);
    sustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        apvts, ParamIDs::sustain, sustainSlider);
    releaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        apvts, ParamIDs::release, releaseSlider);
}

void ADSRSection::setupSlider (juce::Slider& slider, juce::Label& label, const juce::String& text)
{
    slider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 50, 16);
    addAndMakeVisible (slider);

    label.setText (text, juce::dontSendNotification);
    label.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (label);
}

void ADSRSection::paint (juce::Graphics& g)
{
    g.setColour (ErinSynthLookAndFeel::panelColour);
    g.fillRoundedRectangle (getLocalBounds().toFloat(), 6.0f);

    g.setColour (ErinSynthLookAndFeel::accentColour);
    g.drawRoundedRectangle (getLocalBounds().toFloat().reduced (1.0f), 6.0f, 1.0f);

    g.setColour (ErinSynthLookAndFeel::textColour);
    g.setFont (14.0f);
    g.drawText ("ENVELOPE", getLocalBounds().removeFromTop (25), juce::Justification::centred);
}

void ADSRSection::resized()
{
    auto bounds = getLocalBounds().reduced (10);
    bounds.removeFromTop (25);

    int knobWidth = bounds.getWidth() / 4;

    auto setupKnob = [&] (juce::Slider& slider, juce::Label& label)
    {
        auto col = bounds.removeFromLeft (knobWidth);
        label.setBounds (col.removeFromTop (18));
        slider.setBounds (col);
    };

    setupKnob (attackSlider, attackLabel);
    setupKnob (decaySlider, decayLabel);
    setupKnob (sustainSlider, sustainLabel);
    setupKnob (releaseSlider, releaseLabel);
}
