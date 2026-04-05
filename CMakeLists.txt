cmake_minimum_required(VERSION 3.22)
project(ErinSynth VERSION 0.1.0)

set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15" CACHE STRING "Minimum macOS version")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../JUCE ${CMAKE_CURRENT_BINARY_DIR}/JUCE)

juce_add_plugin(ErinSynth
    COMPANY_NAME "Erin"
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    PLUGIN_MANUFACTURER_CODE Erin
    PLUGIN_CODE Erns
    FORMATS VST3 Standalone
    PRODUCT_NAME "ErinSynth")

juce_generate_juce_header(ErinSynth)

target_sources(ErinSynth
    PRIVATE
        Source/PluginProcessor.cpp
        Source/PluginEditor.cpp
        Source/Synth/ErinSynthVoice.cpp
        Source/DSP/Distortion.cpp
        Source/DSP/LevelMeter.cpp
        Source/GUI/VUMeterComponent.cpp
        Source/GUI/OscillatorSection.cpp
        Source/GUI/ADSRSection.cpp
        Source/GUI/DistortionSection.cpp
        Source/GUI/GainSection.cpp
        Source/GUI/ErinSynthLookAndFeel.cpp
        Source/GUI/WaveformVisualizer.cpp
        Source/GUI/FilterEnvSection.cpp
        Source/GUI/FilterSection.cpp
        Source/GUI/LFOSection.cpp)

target_compile_definitions(ErinSynth
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_MODAL_LOOPS_PERMITTED=0)

target_link_libraries(ErinSynth
    PRIVATE
        juce::juce_audio_utils
        juce::juce_dsp
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)
