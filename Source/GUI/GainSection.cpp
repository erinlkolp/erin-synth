#include "GainSection.h"
#include "../ParameterIDs.h"
#include "ErinSynthLookAndFeel.h"

GainSection::GainSection (juce::AudioProcessorValueTreeState& apvts)
{
    gainSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    gainSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 60, 16);
    addAndMakeVisible (gainSlider);

    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        apvts, ParamIDs::masterGain, gainSlider);

    gainLabel.setText ("Gain", juce::dontSendNotification);
    gainLabel.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (gainLabel);
}

void GainSection::paint (juce::Graphics& g)
{
    g.setColour (ErinSynthLookAndFeel::panelColour);
    g.fillRoundedRectangle (getLocalBounds().toFloat(), 6.0f);

    g.setColour (ErinSynthLookAndFeel::accentColour);
    g.drawRoundedRectangle (getLocalBounds().toFloat().reduced (1.0f), 6.0f, 1.0f);

    g.setColour (ErinSynthLookAndFeel::textColour);
    g.setFont (14.0f);
    g.drawText ("OUTPUT", getLocalBounds().removeFromTop (25), juce::Justification::centred);
}

void GainSection::resized()
{
    auto bounds = getLocalBounds().reduced (10);
    bounds.removeFromTop (25);

    gainLabel.setBounds (bounds.removeFromTop (18));
    gainSlider.setBounds (bounds);
}
