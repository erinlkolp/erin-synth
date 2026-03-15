#pragma once

namespace ParamIDs
{
#define PARAMETER_ID(str) constexpr const char* str { #str };

    // Oscillator 1
    PARAMETER_ID (oscWaveform)
    PARAMETER_ID (osc1Level)

    // Oscillator 2
    PARAMETER_ID (osc2Waveform)
    PARAMETER_ID (osc2Level)

    // Sub Oscillator
    PARAMETER_ID (subOscLevel)

    // ADSR
    PARAMETER_ID (attack)
    PARAMETER_ID (decay)
    PARAMETER_ID (sustain)
    PARAMETER_ID (release)

    // Filter
    PARAMETER_ID (filterType)
    PARAMETER_ID (filterCutoff)
    PARAMETER_ID (filterResonance)

    // LFO
    PARAMETER_ID (lfoRate)
    PARAMETER_ID (lfoDepth)

    // Gain
    PARAMETER_ID (masterGain)

    // Distortion
    PARAMETER_ID (distortionEnabled)
    PARAMETER_ID (distortionType)
    PARAMETER_ID (distortionDrive)
    PARAMETER_ID (distortionMix)

#undef PARAMETER_ID
}
