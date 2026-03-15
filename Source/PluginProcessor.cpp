#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ParameterIDs.h"

ErinSynthAudioProcessor::ErinSynthAudioProcessor()
    : AudioProcessor (BusesProperties()
                          .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
      apvts (*this, nullptr, "PARAMETERS", createParameterLayout())
{
    synth.addSound (new ErinSynthSound());

    for (int i = 0; i < numVoices; ++i)
        synth.addVoice (new ErinSynthVoice());
}

ErinSynthAudioProcessor::~ErinSynthAudioProcessor() {}

juce::AudioProcessorValueTreeState::ParameterLayout ErinSynthAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    layout.add (std::make_unique<juce::AudioParameterChoice> (
        juce::ParameterID { ParamIDs::oscWaveform, 1 },
        "Waveform",
        juce::StringArray { "Sine", "Saw", "Square", "Triangle", "Noise" },
        0));

    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { ParamIDs::osc1Level, 1 },
        "OSC 1 Level",
        juce::NormalisableRange<float> (0.0f, 1.0f, 0.01f),
        1.0f));

    layout.add (std::make_unique<juce::AudioParameterChoice> (
        juce::ParameterID { ParamIDs::osc2Waveform, 1 },
        "OSC 2 Waveform",
        juce::StringArray { "Sine", "Saw", "Square", "Triangle", "Noise" },
        1));

    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { ParamIDs::osc2Level, 1 },
        "OSC 2 Level",
        juce::NormalisableRange<float> (0.0f, 1.0f, 0.01f),
        0.0f));

    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { ParamIDs::subOscLevel, 1 },
        "Sub Level",
        juce::NormalisableRange<float> (0.0f, 1.0f, 0.01f),
        0.0f));

    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { ParamIDs::attack, 1 },
        "Attack",
        juce::NormalisableRange<float> (0.001f, 5.0f, 0.001f, 0.3f),
        0.1f));

    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { ParamIDs::decay, 1 },
        "Decay",
        juce::NormalisableRange<float> (0.001f, 5.0f, 0.001f, 0.3f),
        0.1f));

    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { ParamIDs::sustain, 1 },
        "Sustain",
        juce::NormalisableRange<float> (0.0f, 1.0f, 0.01f),
        0.8f));

    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { ParamIDs::release, 1 },
        "Release",
        juce::NormalisableRange<float> (0.001f, 5.0f, 0.001f, 0.3f),
        0.3f));

    layout.add (std::make_unique<juce::AudioParameterChoice> (
        juce::ParameterID { ParamIDs::filterType, 1 },
        "Filter Type",
        juce::StringArray { "Low Pass", "High Pass", "Band Pass" },
        0));

    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { ParamIDs::filterCutoff, 1 },
        "Cutoff",
        juce::NormalisableRange<float> (20.0f, 20000.0f, 1.0f, 0.25f),
        20000.0f));

    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { ParamIDs::filterResonance, 1 },
        "Resonance",
        juce::NormalisableRange<float> (0.1f, 10.0f, 0.01f, 0.5f),
        0.707f));

    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { ParamIDs::filterEnvAttack, 1 },
        "Filter Env Attack",
        juce::NormalisableRange<float> (0.001f, 5.0f, 0.001f, 0.3f),
        0.1f));

    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { ParamIDs::filterEnvDecay, 1 },
        "Filter Env Decay",
        juce::NormalisableRange<float> (0.001f, 5.0f, 0.001f, 0.3f),
        0.2f));

    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { ParamIDs::filterEnvSustain, 1 },
        "Filter Env Sustain",
        juce::NormalisableRange<float> (0.0f, 1.0f, 0.01f),
        0.5f));

    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { ParamIDs::filterEnvRelease, 1 },
        "Filter Env Release",
        juce::NormalisableRange<float> (0.001f, 5.0f, 0.001f, 0.3f),
        0.3f));

    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { ParamIDs::filterEnvDepth, 1 },
        "Filter Env Depth",
        juce::NormalisableRange<float> (0.0f, 4.0f, 0.01f),
        0.0f));

    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { ParamIDs::lfoRate, 1 },
        "LFO Rate",
        juce::NormalisableRange<float> (0.1f, 20.0f, 0.01f, 0.4f),
        1.0f));

    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { ParamIDs::lfoDepth, 1 },
        "LFO Depth",
        juce::NormalisableRange<float> (0.0f, 1.0f, 0.01f),
        0.0f));

    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { ParamIDs::lfoPitchDepth, 1 },
        "LFO Pitch Depth",
        juce::NormalisableRange<float> (0.0f, 24.0f, 0.1f),
        0.0f));

    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { ParamIDs::masterGain, 1 },
        "Master Gain",
        juce::NormalisableRange<float> (-60.0f, 12.0f, 0.1f),
        -6.0f));

    layout.add (std::make_unique<juce::AudioParameterBool> (
        juce::ParameterID { ParamIDs::distortionEnabled, 1 },
        "Distortion Enabled",
        false));

    layout.add (std::make_unique<juce::AudioParameterChoice> (
        juce::ParameterID { ParamIDs::distortionType, 1 },
        "Distortion Type",
        juce::StringArray { "Soft Clip", "Hard Clip", "Foldback", "Bitcrush", "Waveshape" },
        0));

    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { ParamIDs::distortionDrive, 1 },
        "Drive",
        juce::NormalisableRange<float> (0.0f, 40.0f, 0.1f),
        0.0f));

    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { ParamIDs::distortionMix, 1 },
        "Mix",
        juce::NormalisableRange<float> (0.0f, 100.0f, 1.0f),
        100.0f));

    layout.add (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { ParamIDs::ringModMix, 1 },
        "Ring Mod Mix",
        juce::NormalisableRange<float> (0.0f, 100.0f, 1.0f),
        0.0f));

    return layout;
}

void ErinSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate (sampleRate);

    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = static_cast<juce::uint32> (samplesPerBlock);
    spec.numChannels = static_cast<juce::uint32> (getTotalNumOutputChannels());

    this->sampleRate = sampleRate;
    filterEnv.setSampleRate (sampleRate);
    filterEnv.reset();

    filter.prepare (spec);
    filter.setType (juce::dsp::StateVariableTPTFilterType::lowpass);
    distortion.prepare (spec);
    preMeter.prepare (sampleRate);
    postMeter.prepare (sampleRate);
    waveformBuffer.prepare (8192);
}

void ErinSynthAudioProcessor::releaseResources()
{
    filter.reset();
    distortion.reset();
    preMeter.reset();
    postMeter.reset();
    waveformBuffer.reset();
    lfoPhase = 0.0;
    filterEnv.reset();
    heldNoteCount = 0;
}

bool ErinSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    return true;
}

void ErinSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                             juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    buffer.clear();

    // Compute LFO value at start of block (used for pitch modulation in voices)
    float lfoRate  = apvts.getRawParameterValue (ParamIDs::lfoRate)->load();
    double lfoInc  = static_cast<double> (lfoRate) / sampleRate;
    float lfoValue = static_cast<float> (std::sin (2.0 * juce::MathConstants<double>::pi * lfoPhase));

    // Update filter envelope parameters each block
    {
        juce::ADSR::Parameters fep;
        fep.attack  = apvts.getRawParameterValue (ParamIDs::filterEnvAttack)->load();
        fep.decay   = apvts.getRawParameterValue (ParamIDs::filterEnvDecay)->load();
        fep.sustain = apvts.getRawParameterValue (ParamIDs::filterEnvSustain)->load();
        fep.release = apvts.getRawParameterValue (ParamIDs::filterEnvRelease)->load();
        filterEnv.setParameters (fep);
    }

    // Scan MIDI to drive filter envelope
    for (const auto meta : midiMessages)
    {
        const auto msg = meta.getMessage();
        if (msg.isNoteOn())
        {
            heldNoteCount++;
            filterEnv.noteOn();
        }
        else if (msg.isNoteOff())
        {
            heldNoteCount = juce::jmax (0, heldNoteCount - 1);
            if (heldNoteCount == 0)
                filterEnv.noteOff();
        }
    }

    // Push current parameter values to all voices
    {
        ErinSynthVoice::Params voiceParams;
        voiceParams.osc1Waveform  = static_cast<int> (apvts.getRawParameterValue (ParamIDs::oscWaveform)->load());
        voiceParams.osc2Waveform  = static_cast<int> (apvts.getRawParameterValue (ParamIDs::osc2Waveform)->load());
        voiceParams.osc1Level     = apvts.getRawParameterValue (ParamIDs::osc1Level)->load();
        voiceParams.osc2Level     = apvts.getRawParameterValue (ParamIDs::osc2Level)->load();
        voiceParams.subOscLevel   = apvts.getRawParameterValue (ParamIDs::subOscLevel)->load();
        voiceParams.attack        = apvts.getRawParameterValue (ParamIDs::attack)->load();
        voiceParams.decay         = apvts.getRawParameterValue (ParamIDs::decay)->load();
        voiceParams.sustain       = apvts.getRawParameterValue (ParamIDs::sustain)->load();
        voiceParams.release       = apvts.getRawParameterValue (ParamIDs::release)->load();
        voiceParams.lfoValue      = lfoValue;
        voiceParams.lfoPitchDepth = apvts.getRawParameterValue (ParamIDs::lfoPitchDepth)->load();
        voiceParams.ringModMix    = apvts.getRawParameterValue (ParamIDs::ringModMix)->load() / 100.0f;

        for (int i = 0; i < synth.getNumVoices(); ++i)
            if (auto* voice = dynamic_cast<ErinSynthVoice*> (synth.getVoice (i)))
                voice->updateParams (voiceParams);
    }

    // Render synth voices
    synth.renderNextBlock (buffer, midiMessages, 0, buffer.getNumSamples());

    // Apply filter with LFO + filter envelope modulation, per-sample
    {
        int filterTypeIdx = static_cast<int> (apvts.getRawParameterValue (ParamIDs::filterType)->load());
        switch (filterTypeIdx)
        {
            case 0: filter.setType (juce::dsp::StateVariableTPTFilterType::lowpass);  break;
            case 1: filter.setType (juce::dsp::StateVariableTPTFilterType::highpass); break;
            case 2: filter.setType (juce::dsp::StateVariableTPTFilterType::bandpass); break;
        }

        float baseCutoff      = apvts.getRawParameterValue (ParamIDs::filterCutoff)->load();
        float resonance       = apvts.getRawParameterValue (ParamIDs::filterResonance)->load();
        float lfoFilterDepth  = apvts.getRawParameterValue (ParamIDs::lfoDepth)->load();
        float filterEnvDepth  = apvts.getRawParameterValue (ParamIDs::filterEnvDepth)->load();
        int   numSamples      = buffer.getNumSamples();
        int   numChannels     = buffer.getNumChannels();

        filter.setResonance (resonance);

        for (int i = 0; i < numSamples; ++i)
        {
            lfoPhase += lfoInc;
            if (lfoPhase >= 1.0) lfoPhase -= 1.0;

            float lfoSine   = static_cast<float> (std::sin (2.0 * juce::MathConstants<double>::pi * lfoPhase));
            float envVal    = filterEnv.getNextSample();
            float modOctaves = lfoSine * lfoFilterDepth * 4.0f + envVal * filterEnvDepth;
            float modCutoff  = juce::jlimit (20.0f, 20000.0f,
                                             baseCutoff * std::pow (2.0f, modOctaves));
            filter.setCutoffFrequency (modCutoff);

            for (int ch = 0; ch < numChannels; ++ch)
            {
                float* data = buffer.getWritePointer (ch);
                data[i] = filter.processSample (ch, data[i]);
            }
        }
    }

    // Pre-distortion metering
    preMeter.measureBlock (buffer);

    // Apply distortion
    distortion.setEnabled (apvts.getRawParameterValue (ParamIDs::distortionEnabled)->load() > 0.5f);
    distortion.setType (static_cast<Distortion::Type> (
        static_cast<int> (apvts.getRawParameterValue (ParamIDs::distortionType)->load())));
    distortion.setDrive (apvts.getRawParameterValue (ParamIDs::distortionDrive)->load());
    distortion.setMix (apvts.getRawParameterValue (ParamIDs::distortionMix)->load());
    distortion.process (buffer);

    // Apply master gain
    float gainDb     = apvts.getRawParameterValue (ParamIDs::masterGain)->load();
    float gainLinear = juce::Decibels::decibelsToGain (gainDb);
    buffer.applyGain (gainLinear);

    // Post-distortion / output metering
    postMeter.measureBlock (buffer);

    // Feed waveform visualizer
    const float* ch0 = buffer.getReadPointer (0);
    for (int i = 0; i < buffer.getNumSamples(); ++i)
        waveformBuffer.pushSample (ch0[i]);
}

juce::AudioProcessorEditor* ErinSynthAudioProcessor::createEditor()
{
    return new ErinSynthAudioProcessorEditor (*this);
}

void ErinSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void ErinSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xml (getXmlFromBinary (data, sizeInBytes));
    if (xml != nullptr && xml->hasTagName (apvts.state.getType()))
        apvts.replaceState (juce::ValueTree::fromXml (*xml));
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ErinSynthAudioProcessor();
}
