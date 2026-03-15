#include "VUMeterComponent.h"

VUMeterComponent::VUMeterComponent (LevelMeter& meter, const juce::String& label)
    : meterSource (meter), meterLabel (label)
{
    startTimerHz (30);
}

VUMeterComponent::~VUMeterComponent()
{
    stopTimer();
}

void VUMeterComponent::timerCallback()
{
    float newLeft  = meterSource.getLevelLeft();
    float newRight = meterSource.getLevelRight();

    if (std::abs (newLeft - currentLeftDb) > 0.1f || std::abs (newRight - currentRightDb) > 0.1f)
    {
        currentLeftDb  = newLeft;
        currentRightDb = newRight;
        repaint();
    }
}

void VUMeterComponent::drawMeterBar (juce::Graphics& g, juce::Rectangle<float> bounds, float levelDb)
{
    float clampedDb = juce::jlimit (-60.0f, 6.0f, levelDb);
    float proportion = (clampedDb + 60.0f) / 66.0f;

    // Background
    g.setColour (ErinSynthLookAndFeel::panelColour.darker (0.3f));
    g.fillRoundedRectangle (bounds, 2.0f);

    if (proportion <= 0.0f)
        return;

    auto filledHeight = bounds.getHeight() * proportion;
    auto filledBounds = bounds.withTop (bounds.getBottom() - filledHeight);

    // Gradient: green -> yellow -> red
    if (clampedDb < -6.0f)
        g.setColour (ErinSynthLookAndFeel::meterGreen);
    else if (clampedDb < 0.0f)
        g.setColour (ErinSynthLookAndFeel::meterYellow);
    else
        g.setColour (ErinSynthLookAndFeel::meterRed);

    g.fillRoundedRectangle (filledBounds, 2.0f);
}

void VUMeterComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();

    // Label at bottom
    auto labelArea = bounds.removeFromBottom (18.0f);
    g.setColour (ErinSynthLookAndFeel::textColour);
    g.setFont (12.0f);
    g.drawText (meterLabel, labelArea, juce::Justification::centred);

    bounds.removeFromBottom (2.0f);

    float barWidth = (bounds.getWidth() - 4.0f) / 2.0f;
    auto leftBar  = bounds.removeFromLeft (barWidth);
    bounds.removeFromLeft (4.0f);
    auto rightBar = bounds.removeFromLeft (barWidth);

    drawMeterBar (g, leftBar, currentLeftDb);
    drawMeterBar (g, rightBar, currentRightDb);
}
