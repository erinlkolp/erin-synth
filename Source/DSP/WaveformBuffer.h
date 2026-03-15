#pragma once
#include <JuceHeader.h>

class WaveformBuffer
{
public:
    void prepare (int size)
    {
        bufferSize = size;
        buffer.resize (static_cast<size_t> (size), 0.0f);
        writeIndex.store (0, std::memory_order_relaxed);
    }

    void reset()
    {
        std::fill (buffer.begin(), buffer.end(), 0.0f);
        writeIndex.store (0, std::memory_order_relaxed);
    }

    void pushSample (float sample)
    {
        int idx = writeIndex.load (std::memory_order_relaxed);
        buffer[static_cast<size_t> (idx)] = sample;
        writeIndex.store ((idx + 1) % bufferSize, std::memory_order_release);
    }

    void copyLatest (float* dest, int numSamples) const
    {
        int head = writeIndex.load (std::memory_order_acquire);
        int start = (head - numSamples + bufferSize) % bufferSize;

        for (int i = 0; i < numSamples; ++i)
            dest[i] = buffer[static_cast<size_t> ((start + i) % bufferSize)];
    }

    int getBufferSize() const { return bufferSize; }

private:
    std::vector<float> buffer;
    std::atomic<int> writeIndex { 0 };
    int bufferSize = 0;
};
