#pragma once
#include <JuceHeader.h>

class Distortion
{
public:
    enum Type
    {
        SoftClip = 0,
        HardClip,
        Foldback,
        Bitcrush,
        Waveshape,
        NumTypes
    };

    void prepare (const juce::dsp::ProcessSpec& spec);
    void process (juce::AudioBuffer<float>& buffer);
    void reset();

    void setType (Type newType)      { currentType = newType; }
    void setDrive (float driveInDb)  { driveLinear = juce::Decibels::decibelsToGain (driveInDb); }
    void setMix (float mixPercent)   { mixProportion = mixPercent / 100.0f; }
    void setEnabled (bool e)         { enabled = e; }

private:
    float processSample (float input) const;

    Type currentType = SoftClip;
    float driveLinear = 1.0f;
    float mixProportion = 1.0f;
    bool enabled = false;
};
