#include "WaveformVisualizer.h"

WaveformVisualizer::WaveformVisualizer (WaveformBuffer& buffer)
    : waveformSource (buffer),
      displayBuffer (static_cast<size_t> (displaySize), 0.0f)
{
    startTimerHz (30);
}

WaveformVisualizer::~WaveformVisualizer()
{
    stopTimer();
}

void WaveformVisualizer::timerCallback()
{
    if (waveformSource.getBufferSize() > 0)
    {
        waveformSource.copyLatest (displayBuffer.data(), displaySize);
        repaint();
    }
}

void WaveformVisualizer::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();

    g.setColour (ErinSynthLookAndFeel::panelColour);
    g.fillRoundedRectangle (bounds, 6.0f);

    g.setColour (ErinSynthLookAndFeel::accentColour);
    g.drawRoundedRectangle (bounds.reduced (1.0f), 6.0f, 1.0f);

    g.setColour (ErinSynthLookAndFeel::textColour);
    g.setFont (14.0f);
    g.drawText ("WAVEFORM", getLocalBounds().removeFromTop (20), juce::Justification::centred);

    auto area = getLocalBounds().reduced (10);
    area.removeFromTop (16);

    float centreY = static_cast<float> (area.getCentreY());
    float halfH = static_cast<float> (area.getHeight()) * 0.5f;

    // Zero-crossing line
    g.setColour (ErinSynthLookAndFeel::accentColour.withAlpha (0.4f));
    g.drawHorizontalLine (static_cast<int> (centreY), static_cast<float> (area.getX()),
                          static_cast<float> (area.getRight()));

    // Waveform path
    juce::Path path;
    float xStep = static_cast<float> (area.getWidth()) / static_cast<float> (displaySize - 1);

    for (int i = 0; i < displaySize; ++i)
    {
        float x = static_cast<float> (area.getX()) + static_cast<float> (i) * xStep;
        float y = centreY - displayBuffer[static_cast<size_t> (i)] * halfH;

        if (i == 0)
            path.startNewSubPath (x, y);
        else
            path.lineTo (x, y);
    }

    g.setColour (ErinSynthLookAndFeel::accentColour.brighter (0.5f));
    g.strokePath (path, juce::PathStrokeType (1.5f));
}
