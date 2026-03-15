#pragma once
#include <JuceHeader.h>
#include "ErinSynthSound.h"

class ErinSynthVoice : public juce::SynthesiserVoice
{
public:
    struct Params
    {
        int osc1Waveform = 0;
        int osc2Waveform = 0;
        float osc1Level = 1.0f;
        float osc2Level = 0.0f;
        float subOscLevel = 0.0f;
        float attack = 0.1f;
        float decay = 0.1f;
        float sustain = 0.8f;
        float release = 0.3f;
    };

    void updateParams (const Params& p);

    bool canPlaySound (juce::SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity,
                    juce::SynthesiserSound*, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void pitchWheelMoved (int newValue) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void renderNextBlock (juce::AudioBuffer<float>& outputBuffer,
                          int startSample, int numSamples) override;

private:
    float generateSample (int waveform, double phase);

    juce::ADSR adsr;
    float velocityLevel = 0.0f;

    // Oscillator 1
    double phase = 0.0;
    double phaseIncrement = 0.0;

    // Oscillator 2
    double osc2Phase = 0.0;
    double osc2PhaseIncrement = 0.0;

    // Sub oscillator
    double subPhase = 0.0;
    double subPhaseIncrement = 0.0;

    Params currentParams;
};
