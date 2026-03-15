#include "ErinSynthVoice.h"

void ErinSynthVoice::updateParams (const Params& p)
{
    currentParams = p;
}

bool ErinSynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<ErinSynthSound*> (sound) != nullptr;
}

void ErinSynthVoice::startNote (int midiNoteNumber, float velocity,
                                juce::SynthesiserSound*, int /*currentPitchWheelPosition*/)
{
    phase = 0.0;
    osc2Phase = 0.0;
    subPhase = 0.0;
    velocityLevel = velocity;

    phaseIncrement = juce::MidiMessage::getMidiNoteInHertz (midiNoteNumber) / getSampleRate();
    osc2PhaseIncrement = phaseIncrement;
    subPhaseIncrement = phaseIncrement * 0.5; // one octave below

    basePhaseIncrement    = phaseIncrement;
    osc2BasePhaseIncrement = osc2PhaseIncrement;
    subBasePhaseIncrement  = subPhaseIncrement;

    juce::ADSR::Parameters adsrParams;
    adsrParams.attack  = currentParams.attack;
    adsrParams.decay   = currentParams.decay;
    adsrParams.sustain = currentParams.sustain;
    adsrParams.release = currentParams.release;
    adsr.setParameters (adsrParams);
    adsr.setSampleRate (getSampleRate());
    adsr.noteOn();
}

void ErinSynthVoice::stopNote (float /*velocity*/, bool allowTailOff)
{
    if (allowTailOff)
    {
        adsr.noteOff();
    }
    else
    {
        adsr.reset();
        clearCurrentNote();
    }
}

void ErinSynthVoice::pitchWheelMoved (int) {}
void ErinSynthVoice::controllerMoved (int, int) {}

float ErinSynthVoice::generateSample (int waveform, double ph)
{
    switch (waveform)
    {
        case 0: // Sine
            return static_cast<float> (std::sin (2.0 * juce::MathConstants<double>::pi * ph));
        case 1: // Saw
            return static_cast<float> (2.0 * ph - 1.0);
        case 2: // Square
            return ph < 0.5 ? 1.0f : -1.0f;
        case 3: // Triangle
            return static_cast<float> (4.0 * std::abs (ph - 0.5) - 1.0);
        case 4: // White Noise
            return juce::Random::getSystemRandom().nextFloat() * 2.0f - 1.0f;
        default:
            return 0.0f;
    }
}

void ErinSynthVoice::renderNextBlock (juce::AudioBuffer<float>& outputBuffer,
                                       int startSample, int numSamples)
{
    if (! isVoiceActive())
        return;

    // Update ADSR parameters every block
    juce::ADSR::Parameters adsrParams;
    adsrParams.attack  = currentParams.attack;
    adsrParams.decay   = currentParams.decay;
    adsrParams.sustain = currentParams.sustain;
    adsrParams.release = currentParams.release;
    adsr.setParameters (adsrParams);

    int wf1 = currentParams.osc1Waveform;
    int wf2 = currentParams.osc2Waveform;
    float lvl1 = currentParams.osc1Level;
    float lvl2 = currentParams.osc2Level;
    float subLvl = currentParams.subOscLevel;

    // Compute pitch-modulated phase increments from LFO (block-rate)
    float pitchMod = std::pow (2.0f, currentParams.lfoValue * currentParams.lfoPitchDepth / 12.0f);
    double modPhaseInc    = basePhaseIncrement     * static_cast<double> (pitchMod);
    double modOsc2PhaseInc = osc2BasePhaseIncrement * static_cast<double> (pitchMod);
    double modSubPhaseInc  = subBasePhaseIncrement  * static_cast<double> (pitchMod);

    float ringMix = currentParams.ringModMix;

    for (int i = 0; i < numSamples; ++i)
    {
        float envValue = adsr.getNextSample();

        float osc1 = generateSample (wf1, phase);
        float osc2 = generateSample (wf2, osc2Phase);
        float sub  = generateSample (0,   subPhase);

        float normalSample  = osc1 * lvl1 + osc2 * lvl2 + sub * subLvl;
        float ringModSample = osc1 * osc2;
        float mixed = normalSample * (1.0f - ringMix) + ringModSample * ringMix;

        float sample = mixed * velocityLevel * envValue;

        for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            outputBuffer.addSample (channel, startSample + i, sample);

        phase     += modPhaseInc;
        if (phase     >= 1.0) phase     -= 1.0;

        osc2Phase += modOsc2PhaseInc;
        if (osc2Phase >= 1.0) osc2Phase -= 1.0;

        subPhase  += modSubPhaseInc;
        if (subPhase  >= 1.0) subPhase  -= 1.0;

        if (! adsr.isActive())
        {
            clearCurrentNote();
            break;
        }
    }
}
