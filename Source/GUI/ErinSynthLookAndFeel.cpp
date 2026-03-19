#include "ErinSynthLookAndFeel.h"

const juce::Colour ErinSynthLookAndFeel::backgroundColour = juce::Colour (0xff12121f);
const juce::Colour ErinSynthLookAndFeel::panelColour      = juce::Colour (0xff16213e);
const juce::Colour ErinSynthLookAndFeel::accentColour     = juce::Colour (0xff0f3460);
const juce::Colour ErinSynthLookAndFeel::meterGreen       = juce::Colour (0xff00e676);
const juce::Colour ErinSynthLookAndFeel::meterYellow      = juce::Colour (0xffffc107);
const juce::Colour ErinSynthLookAndFeel::meterRed         = juce::Colour (0xffff1744);
const juce::Colour ErinSynthLookAndFeel::textColour       = juce::Colour (0xffe0e0e0);

ErinSynthLookAndFeel::ErinSynthLookAndFeel()
{
    setColour (juce::ResizableWindow::backgroundColourId, backgroundColour);
    setColour (juce::Slider::thumbColourId, accentColour.brighter (0.3f));
    setColour (juce::Slider::rotarySliderFillColourId, accentColour);
    setColour (juce::Slider::rotarySliderOutlineColourId, panelColour.brighter (0.2f));
    setColour (juce::Label::textColourId, textColour);
    setColour (juce::ComboBox::backgroundColourId, panelColour);
    setColour (juce::ComboBox::textColourId, textColour);
    setColour (juce::ComboBox::outlineColourId, accentColour);
    setColour (juce::ToggleButton::tickColourId, accentColour.brighter (0.4f));
    setColour (juce::ToggleButton::tickDisabledColourId, panelColour.brighter (0.1f));
    setColour (juce::PopupMenu::backgroundColourId, panelColour);
    setColour (juce::PopupMenu::textColourId, textColour);
    setColour (juce::PopupMenu::highlightedBackgroundColourId, accentColour);
}

void ErinSynthLookAndFeel::drawRotarySlider (juce::Graphics& g, int x, int y,
                                              int width, int height,
                                              float sliderPos,
                                              float rotaryStartAngle,
                                              float rotaryEndAngle,
                                              juce::Slider&)
{
    auto bounds = juce::Rectangle<int> (x, y, width, height).toFloat().reduced (4.0f);
    auto radius = juce::jmin (bounds.getWidth(), bounds.getHeight()) / 2.0f;
    auto centreX = bounds.getCentreX();
    auto centreY = bounds.getCentreY();
    auto rx = centreX - radius;
    auto ry = centreY - radius;
    auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    // Background arc
    juce::Path bgArc;
    bgArc.addCentredArc (centreX, centreY, radius - 2.0f, radius - 2.0f,
                         0.0f, rotaryStartAngle, rotaryEndAngle, true);
    g.setColour (panelColour.brighter (0.15f));
    g.strokePath (bgArc, juce::PathStrokeType (3.0f, juce::PathStrokeType::curved,
                                                juce::PathStrokeType::rounded));

    // Value arc
    juce::Path valueArc;
    valueArc.addCentredArc (centreX, centreY, radius - 2.0f, radius - 2.0f,
                            0.0f, rotaryStartAngle, angle, true);
    g.setColour (accentColour.brighter (0.3f));
    g.strokePath (valueArc, juce::PathStrokeType (3.0f, juce::PathStrokeType::curved,
                                                   juce::PathStrokeType::rounded));

    // Thumb dot
    juce::Path thumb;
    auto thumbWidth = 5.0f;
    thumb.addEllipse (-thumbWidth / 2.0f, -radius + 4.0f, thumbWidth, thumbWidth);
    g.setColour (textColour);
    g.fillPath (thumb, juce::AffineTransform::rotation (angle).translated (centreX, centreY));
}
