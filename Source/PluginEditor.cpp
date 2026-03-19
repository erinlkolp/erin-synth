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
      filterEnvSection (p.apvts),
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
    addAndMakeVisible (filterEnvSection);
    addAndMakeVisible (distortionSection);
    addAndMakeVisible (gainSection);
    addAndMakeVisible (waveformVisualizer);

    setSize (900, 700);
}

ErinSynthAudioProcessorEditor::~ErinSynthAudioProcessorEditor()
{
    setLookAndFeel (nullptr);
}

void ErinSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();

    // Gradient background: dark top to deep purple bottom
    juce::ColourGradient gradient (juce::Colour (0xff12121f), 0.0f, 0.0f,
                                   juce::Colour (0xff1f1230), 0.0f, bounds.getHeight(),
                                   false);
    g.setGradientFill (gradient);
    g.fillRect (bounds);

    // Subtle noise texture overlay
    {
        juce::Random rng (42); // fixed seed for deterministic pattern
        g.setColour (juce::Colours::white.withAlpha (0.012f));

        auto w = getWidth();
        auto h = getHeight();

        for (int yy = 0; yy < h; yy += 2)
        {
            for (int xx = 0; xx < w; xx += 2)
            {
                if (rng.nextFloat() < 0.3f)
                    g.fillRect (xx, yy, 1, 1);
            }
        }
    }

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

    // Row 1 (top 42%): Oscillators | ADSR | Filter / LFO / FilterEnv stacked
    auto topRow = bounds.removeFromTop (static_cast<int> (bounds.getHeight() * 0.42f));
    bounds.removeFromTop (gap);

    int col1W = topRow.getWidth() * 3 / 10;
    int col2W = topRow.getWidth() * 4 / 10;

    oscillatorSection.setBounds (topRow.removeFromLeft (col1W));
    topRow.removeFromLeft (gap);
    adsrSection.setBounds (topRow.removeFromLeft (col2W));
    topRow.removeFromLeft (gap);

    // Right column: Filter / LFO / FilterEnv stacked
    auto rightCol = topRow;
    int filterH   = static_cast<int> (rightCol.getHeight() * 0.35f);
    int lfoH      = static_cast<int> (rightCol.getHeight() * 0.22f);

    filterSection.setBounds (rightCol.removeFromTop (filterH));
    rightCol.removeFromTop (gap);
    lfoSection.setBounds (rightCol.removeFromTop (lfoH));
    rightCol.removeFromTop (gap);
    filterEnvSection.setBounds (rightCol);

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
