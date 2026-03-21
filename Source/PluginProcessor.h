#pragma once
#include <JuceHeader.h>
#include "Synth/ErinSynthSound.h"
#include "Synth/ErinSynthVoice.h"
#include "DSP/Distortion.h"
#include "DSP/LevelMeter.h"
#include "DSP/WaveformBuffer.h"

class ErinSynthAudioProcessor : public juce::AudioProcessor
{
public:
    ErinSynthAudioProcessor();
    ~ErinSynthAudioProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return JucePlugin_Name; }
    bool acceptsMidi() const override  { return true; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }

    int getNumPrograms() override    { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram (int) override {}
    const juce::String getProgramName (int) override { return {}; }
    void changeProgramName (int, const juce::String&) override {}

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState apvts;
    LevelMeter& getPreMeter()  { return preMeter; }
    LevelMeter& getPostMeter() { return postMeter; }
    WaveformBuffer& getWaveformBuffer() { return waveformBuffer; }

private:
    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    juce::Synthesiser synth;
    juce::dsp::StateVariableTPTFilter<float> filter;
    Distortion distortion;
    LevelMeter preMeter;
    LevelMeter postMeter;
    WaveformBuffer waveformBuffer;

    juce::SmoothedValue<float> smoothedMasterGain;
    double lfoPhase = 0.0;
    double sampleRate = 44100.0;

    juce::ADSR filterEnv;
    int heldNoteCount = 0;

    static constexpr int numVoices = 8;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ErinSynthAudioProcessor)
};
