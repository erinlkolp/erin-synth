#include "FilterEnvSection.h"
#include "../ParameterIDs.h"
#include "ErinSynthLookAndFeel.h"

FilterEnvSection::FilterEnvSection (juce::AudioProcessorValueTreeState& apvts)
{
    setupSlider (depthSlider,   depthLabel,   "Dep");
    setupSlider (attackSlider,  attackLabel,  "A");
    setupSlider (decaySlider,   decayLabel,   "D");
    setupSlider (sustainSlider, sustainLabel, "S");
    setupSlider (releaseSlider, releaseLabel, "R");

    depthAttachment   = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        apvts, ParamIDs::filterEnvDepth,   depthSlider);
    attackAttachment  = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        apvts, ParamIDs::filterEnvAttack,  attackSlider);
    decayAttachment   = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        apvts, ParamIDs::filterEnvDecay,   decaySlider);
    sustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        apvts, ParamIDs::filterEnvSustain, sustainSlider);
    releaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        apvts, ParamIDs::filterEnvRelease, releaseSlider);
}

void FilterEnvSection::setupSlider (juce::Slider& slider, juce::Label& label, const juce::String& text)
{
    slider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 44, 14);
    addAndMakeVisible (slider);

    label.setText (text, juce::dontSendNotification);
    label.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (label);
}

void FilterEnvSection::paint (juce::Graphics& g)
{
    g.setColour (ErinSynthLookAndFeel::panelColour);
    g.fillRoundedRectangle (getLocalBounds().toFloat(), 6.0f);

    g.setColour (ErinSynthLookAndFeel::accentColour);
    g.drawRoundedRectangle (getLocalBounds().toFloat().reduced (1.0f), 6.0f, 1.0f);

    g.setColour (ErinSynthLookAndFeel::textColour);
    g.setFont (14.0f);
    g.drawText ("FILTER ENV", getLocalBounds().removeFromTop (25), juce::Justification::centred);
}

void FilterEnvSection::resized()
{
    auto bounds = getLocalBounds().reduced (10);
    bounds.removeFromTop (25);

    int knobWidth = bounds.getWidth() / 5;

    auto setupKnob = [&] (juce::Slider& slider, juce::Label& label)
    {
        auto col = bounds.removeFromLeft (knobWidth);
        label.setBounds (col.removeFromTop (16));
        slider.setBounds (col);
    };

    setupKnob (depthSlider,   depthLabel);
    setupKnob (attackSlider,  attackLabel);
    setupKnob (decaySlider,   decayLabel);
    setupKnob (sustainSlider, sustainLabel);
    setupKnob (releaseSlider, releaseLabel);
}
