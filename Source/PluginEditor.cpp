#include "PluginEditor.h"

ErinSynthAudioProcessorEditor::ErinSynthAudioProcessorEditor (ErinSynthAudioProcessor& p)
    : AudioProcessorEditor (&p),
      processorRef (p),
      preMeter (p.getPreMeter(), "IN"),
      postMeter (p.getPostMeter(), "OUT"),
      oscillatorSection (p.apvts),
      adsrSection (p.apvts),
      filterSection (p.apvts),
      lfoSection (p.apvts),
      distortionSection (p.apvts),
      gainSection (p.apvts),
      waveformVisualizer (p.getWaveformBuffer())
{
    setLookAndFeel (&lookAndFeel);

    addAndMakeVisible (preMeter);
    addAndMakeVisible (postMeter);
    addAndMakeVisible (oscillatorSection);
    addAndMakeVisible (adsrSection);
    addAndMakeVisible (filterSection);
    addAndMakeVisible (lfoSection);
    addAndMakeVisible (distortionSection);
    addAndMakeVisible (gainSection);
    addAndMakeVisible (waveformVisualizer);

    setSize (900, 600);
}

ErinSynthAudioProcessorEditor::~ErinSynthAudioProcessorEditor()
{
    setLookAndFeel (nullptr);
}

void ErinSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (ErinSynthLookAndFeel::backgroundColour);

    g.setColour (ErinSynthLookAndFeel::textColour);
    g.setFont (20.0f);
    g.drawText ("ErinSynth", getLocalBounds().removeFromTop (35), juce::Justification::centred);
}

void ErinSynthAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds().reduced (8);
    bounds.removeFromTop (30); // title area

    constexpr int gap = 8;

    // VU meters on sides
    auto preMeterArea  = bounds.removeFromLeft (36);
    auto postMeterArea = bounds.removeFromRight (36);
    bounds.removeFromLeft (gap);
    bounds.removeFromRight (gap);

    preMeter.setBounds (preMeterArea);
    postMeter.setBounds (postMeterArea);

    // Row 1 (top): Oscillators | ADSR | Filter + LFO
    auto topRow = bounds.removeFromTop (static_cast<int> (bounds.getHeight() * 0.40f));
    bounds.removeFromTop (gap);

    int col1W = topRow.getWidth() * 3 / 10;
    int col2W = topRow.getWidth() * 4 / 10;

    oscillatorSection.setBounds (topRow.removeFromLeft (col1W));
    topRow.removeFromLeft (gap);
    adsrSection.setBounds (topRow.removeFromLeft (col2W));
    topRow.removeFromLeft (gap);

    // Filter + LFO stacked in the right column
    auto filterLfoArea = topRow;
    int filterH = filterLfoArea.getHeight() * 3 / 5;
    filterSection.setBounds (filterLfoArea.removeFromTop (filterH - gap / 2));
    filterLfoArea.removeFromTop (gap);
    lfoSection.setBounds (filterLfoArea);

    // Row 2 (middle): Waveform visualizer
    auto midRow = bounds.removeFromTop (static_cast<int> (bounds.getHeight() * 0.30f));
    bounds.removeFromTop (gap);
    waveformVisualizer.setBounds (midRow);

    // Row 3 (bottom): Distortion | Gain
    auto bottomRow = bounds;
    int distWidth = bottomRow.getWidth() * 2 / 3;
    distortionSection.setBounds (bottomRow.removeFromLeft (distWidth - gap / 2));
    bottomRow.removeFromLeft (gap);
    gainSection.setBounds (bottomRow);
}
