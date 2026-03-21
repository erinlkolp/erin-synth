# ErinSynth — Claude Code Instructions

## Build

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel 2
```

Use `Release` for DAW-loadable binaries (5 MB). `Debug` produces a 97 MB unstripped binary that DAWs may refuse to load. Always use `--parallel 2` to avoid locking the machine.

JUCE must be present at `../JUCE` (sibling of this repo root).

### Installing for DAW use

```bash
cp -r build/ErinSynth_artefacts/Release/VST3/ErinSynth.vst3 ~/.vst3/
```

If Mixbus fails to scan after reinstalling, clear the stale scan cache:
```bash
rm -f ~/.config/mixbus10/plugin_metadata/scan_log
```

## Project layout

| Path | Purpose |
|------|---------|
| `Source/PluginProcessor.*` | AudioProcessor + APVTS parameter layout |
| `Source/PluginEditor.*` | Top-level editor, lays out all GUI sections |
| `Source/ParameterIDs.h` | All parameter ID strings (single source of truth) |
| `Source/DSP/` | Audio-rate processing: distortion, level metering, waveform buffer |
| `Source/Synth/` | Polyphonic voice and sound classes |
| `Source/GUI/` | Individual UI sections (one component per synth section) |

## Conventions

- Parameter IDs live **only** in `ParameterIDs.h` — never hardcode strings elsewhere.
- All APVTS parameters are declared in `PluginProcessor::createParameterLayout()`.
- GUI sections receive `juce::AudioProcessorValueTreeState&` in their constructor and own their APVTS attachments.
- LookAndFeel customisation goes in `ErinSynthLookAndFeel` — don't override `paintXxx` methods ad-hoc in individual components.
- DSP processors (`Distortion`, `LevelMeter`) follow the JUCE `prepare / process / reset` pattern.

## Key types

- `ErinSynthAudioProcessor` — owns the synth, filter, distortion, level meters, and waveform buffer.
- `ErinSynthVoice` — single polyphonic voice; implements oscillator mix (osc1 + osc2 + sub), ADSR.
- `Distortion` — waveshaper; supports multiple distortion algorithms.
- `LevelMeter` — thread-safe RMS meter; `preMeter` is pre-distortion, `postMeter` is post.
- `WaveformBuffer` — lock-free ring buffer written from the audio thread, read by `WaveformVisualizer`.

## Formats

Builds VST3 + Standalone. Plugin code `Erns`, manufacturer `Erin`.
