#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GUI/ErinSynthLookAndFeel.h"
#include "GUI/VUMeterComponent.h"
#include "GUI/OscillatorSection.h"
#include "GUI/ADSRSection.h"
#include "GUI/FilterSection.h"
#include "GUI/LFOSection.h"
#include "GUI/DistortionSection.h"
#include "GUI/GainSection.h"
#include "GUI/WaveformVisualizer.h"

class ErinSynthAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit ErinSynthAudioProcessorEditor (ErinSynthAudioProcessor&);
    ~ErinSynthAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    ErinSynthAudioProcessor& processorRef;
    ErinSynthLookAndFeel lookAndFeel;

    VUMeterComponent preMeter;
    VUMeterComponent postMeter;

    OscillatorSection oscillatorSection;
    ADSRSection adsrSection;
    FilterSection filterSection;
    LFOSection lfoSection;
    DistortionSection distortionSection;
    GainSection gainSection;
    WaveformVisualizer waveformVisualizer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ErinSynthAudioProcessorEditor)
};
