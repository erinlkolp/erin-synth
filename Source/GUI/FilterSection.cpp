#include "FilterSection.h"
#include "../ParameterIDs.h"
#include "ErinSynthLookAndFeel.h"

FilterSection::FilterSection (juce::AudioProcessorValueTreeState& apvts)
{
    typeBox.addItemList ({ "Low Pass", "High Pass", "Band Pass" }, 1);
    addAndMakeVisible (typeBox);
    typeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment> (
        apvts, ParamIDs::filterType, typeBox);

    typeLabel.setText ("Type", juce::dontSendNotification);
    typeLabel.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (typeLabel);

    cutoffSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    cutoffSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 60, 14);
    cutoffSlider.setTextValueSuffix (" Hz");
    addAndMakeVisible (cutoffSlider);
    cutoffAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        apvts, ParamIDs::filterCutoff, cutoffSlider);

    cutoffLabel.setText ("Cutoff", juce::dontSendNotification);
    cutoffLabel.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (cutoffLabel);

    resonanceSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    resonanceSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 44, 14);
    addAndMakeVisible (resonanceSlider);
    resonanceAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        apvts, ParamIDs::filterResonance, resonanceSlider);

    resonanceLabel.setText ("Reso", juce::dontSendNotification);
    resonanceLabel.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (resonanceLabel);
}

void FilterSection::paint (juce::Graphics& g)
{
    g.setColour (ErinSynthLookAndFeel::panelColour);
    g.fillRoundedRectangle (getLocalBounds().toFloat(), 6.0f);

    g.setColour (ErinSynthLookAndFeel::accentColour);
    g.drawRoundedRectangle (getLocalBounds().toFloat().reduced (1.0f), 6.0f, 1.0f);

    g.setColour (ErinSynthLookAndFeel::textColour);
    g.setFont (14.0f);
    g.drawText ("FILTER", getLocalBounds().removeFromTop (25), juce::Justification::centred);
}

void FilterSection::resized()
{
    auto bounds = getLocalBounds().reduced (10);
    bounds.removeFromTop (25);

    // Type selector at top
    typeLabel.setBounds (bounds.removeFromTop (16));
    bounds.removeFromTop (2);
    typeBox.setBounds (bounds.removeFromTop (22));
    bounds.removeFromTop (6);

    // Two knobs side by side
    auto knobArea = bounds;
    int knobW = knobArea.getWidth() / 2;

    auto leftKnob = knobArea.removeFromLeft (knobW);
    cutoffLabel.setBounds (leftKnob.removeFromTop (14));
    cutoffSlider.setBounds (leftKnob);

    resonanceLabel.setBounds (knobArea.removeFromTop (14));
    resonanceSlider.setBounds (knobArea);
}
