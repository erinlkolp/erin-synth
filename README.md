# ErinSynth

A polyphonic synthesizer VST3 plugin built with [JUCE](https://juce.com/) and CMake.

## Features

- **Two oscillators** with selectable waveforms: sine, saw, square, triangle, noise
- **Sub oscillator** with independent level control
- **ADSR envelope** (attack, decay, sustain, release)
- **State-variable filter** with low-pass, high-pass, and band-pass modes; cutoff and resonance controls
- **LFO** with rate and depth controls
- **Distortion** with multiple types, drive, and dry/wet mix
- **Master gain** control
- **VU meter** showing pre- and post-distortion levels
- **Waveform visualizer**
- 8-voice polyphony

## Formats

- VST3
- Standalone application

## Requirements

- CMake 3.22+
- C++17-capable compiler (GCC 9+, Clang 10+, MSVC 2019+)
- [JUCE](https://github.com/juce-framework/JUCE) (see below)

## Building

### 1. Get JUCE

JUCE is expected as a sibling directory to this repo:

```
workspace/
  JUCE/           ← clone here
  erin-synth/     ← this repo
```

```bash
git clone https://github.com/juce-framework/JUCE ../JUCE
```

### 2. Configure and build

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

Built artifacts will be in `build/ErinSynth_artefacts/Release/`:

- `VST3/ErinSynth.vst3` — install to your VST3 folder
- `Standalone/ErinSynth` — run directly

### Platform-specific VST3 install locations

| Platform | Path |
|----------|------|
| Linux    | `~/.vst3/` |
| macOS    | `~/Library/Audio/Plug-Ins/VST3/` |
| Windows  | `%CommonProgramFiles%\VST3\` |

## Project Structure

```
Source/
  PluginProcessor.{h,cpp}   — AudioProcessor, APVTS, DSP chain
  PluginEditor.{h,cpp}      — Top-level editor component
  ParameterIDs.h            — Compile-time parameter ID strings
  DSP/
    Distortion.{h,cpp}      — Waveshaper distortion processor
    LevelMeter.{h,cpp}      — RMS level measurement
    WaveformBuffer.h        — Ring buffer for waveform display
  Synth/
    ErinSynthSound.h        — JUCE SynthesiserSound
    ErinSynthVoice.{h,cpp}  — Polyphonic voice with oscillators + ADSR
  GUI/
    OscillatorSection       — Osc 1/2 and sub-osc controls
    ADSRSection             — Envelope controls
    FilterSection           — Filter type, cutoff, resonance
    LFOSection              — LFO rate and depth
    DistortionSection       — Distortion controls
    GainSection             — Master gain
    VUMeterComponent        — VU meter display
    WaveformVisualizer      — Oscilloscope display
    ErinSynthLookAndFeel    — Custom JUCE LookAndFeel
```

## License

All rights reserved. Personal project by Erin.
