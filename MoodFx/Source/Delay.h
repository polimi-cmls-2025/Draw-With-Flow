#pragma once
#include <JuceHeader.h>
#include "Parameters.h"

class BaseDelay
{
public:
    BaseDelay() {}
    
    ~BaseDelay() {}
    
    void prepareToPlay (const double sr, const int maxNumSamples)
    {
        sampleRate = sr;
        memorySize = roundToInt(Parameters::MAX_DELAY_TIME * sr) + maxNumSamples;
        delayMemory.setSize(2, memorySize);
        delayMemory.clear();
        initialize();
    }
    
    void releaseResources()
    {
        delayMemory.setSize(0, 0);
        memorySize = 0;
    }
    
    void processBlock (AudioBuffer<float>& buffer)
    {
        store(buffer);
        pullTo(buffer);
        advanceWritePosition(buffer.getNumSamples());
    }
    
protected:
    
    virtual void initialize ()
    {
    }
    
    void store (const AudioBuffer<float>& buffer)
    {
        const auto numCh = buffer.getNumChannels();
        const auto numInputSamples = buffer.getNumSamples();
        
        for (int ch = 0; ch < numCh; ++ch)
            if (writeIndex + numInputSamples <= memorySize)
                delayMemory.copyFrom(ch, writeIndex, buffer, ch, 0, numInputSamples);
            else
            {
                const auto fittingSamples = memorySize - writeIndex;
                const auto remainingSamples = numInputSamples - fittingSamples;
                
                delayMemory.copyFrom(ch, writeIndex, buffer, ch, 0, fittingSamples);
                delayMemory.copyFrom(ch, 0, buffer, ch, fittingSamples, remainingSamples);
            }
    }
    
    virtual void pullTo(AudioBuffer<float>& buffer) = 0;
    
    void advanceWritePosition (const int leap)
    {
        writeIndex += leap;
        writeIndex %= memorySize;
    }
    
    AudioBuffer<float> delayMemory;
    double sampleRate = 1.0;
    int writeIndex = 0;
    int memorySize = 0;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BaseDelay)
};


class ModDelay : public BaseDelay
{
public:
    ModDelay() {}
    
    ~ModDelay() {}
    
    void setFeedback (double newFeedback)
    {
        feedback = newFeedback;
    }
    
    void processBlock (AudioBuffer<float>& buffer, AudioBuffer<double>& modulation)
    {
        store(buffer);
        pullTo(buffer, modulation);
        advanceWritePosition(buffer.getNumSamples());
    }
    
private:
    
    double feedback;
    
    void initialize () override
    {
    }
    
    void pullTo (AudioBuffer<float>& buffer) override {}
    
    void pullTo (AudioBuffer<float>& buffer, AudioBuffer<double>& modulation)
    {
        const auto numSamples = buffer.getNumSamples();
        const auto numChannels = buffer.getNumChannels();
        const auto numModulationChannels = modulation.getNumChannels();
        
        auto outputData = buffer.getArrayOfWritePointers();
        auto delayData = delayMemory.getArrayOfWritePointers();
        
        auto modulationData = modulation.getArrayOfReadPointers();
        
        for (int smp = 0; smp < numSamples; ++smp)
        {
            for (int ch = 0; ch < numChannels; ++ ch)
            {
                auto dt = modulationData[jmin(ch, numModulationChannels - 1)][smp];
                auto actualWriteIndex = (writeIndex + smp) % memorySize;
                auto actualReadIndex = actualWriteIndex  - (dt * sampleRate) + memorySize;
                
                auto integerPart = static_cast<int>(actualReadIndex);
                auto fractionalPart = actualReadIndex - integerPart;
                
                auto A = (integerPart + memorySize) % memorySize;
                auto B = (A + 1) % memorySize;
                
                auto alpha = fractionalPart / (2.0 - fractionalPart);
                
                auto sampleValue = alpha * (delayData[ch][B] - oldSample[ch]) + delayData[ch][A];
                oldSample[ch] = sampleValue;
                
                outputData[ch][smp] = sampleValue;
                delayData[ch][actualWriteIndex] += sampleValue * feedback;
            }
        }
    }

    int numChannels = 2;
    
    float oldSample[2] = {0.0f, 0.0f};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModDelay)
};

class AnalogDelay
{
public:
    AnalogDelay(double defaultDelayTime = Parameters::DEFAULT_DELAY_TIME, float defaultFeedback = Parameters::DEFAULT_FEEDBACK)
    {
        delayTime.setCurrentAndTargetValue(defaultDelayTime);
        feedback.setCurrentAndTargetValue(defaultFeedback);
    }

    ~AnalogDelay()     {}

    void prepareToPlay(double sr, float maxNumSamples)
    {
        sampleRate = sr;
        memorySize = roundToInt(Parameters::MAX_DELAY_TIME * sampleRate) + maxNumSamples;
        delayMemory.setSize(2, memorySize);
        delayMemory.clear();
        delayTime.reset(sampleRate, 0.300);
        feedback.reset(sampleRate, 0.020);
    }

    void releaseResources()
    {
        delayMemory.setSize(0, 0);
        memorySize = 0;
    }

    void processBlock(AudioBuffer<float>& buffer)
    {
        const auto numCh = buffer.getNumChannels();
        const auto numInputSamples = buffer.getNumSamples();

        auto bufferData = buffer.getArrayOfWritePointers();
        auto delayData = delayMemory.getArrayOfWritePointers();

        for (int smp = 0; smp < numInputSamples; ++smp)
        {
            auto dt = delayTime.getNextValue();
            auto fb = feedback.getNextValue();

            auto readIndex = writeIndex - (dt * sampleRate);

            auto integerPart = static_cast<int>(readIndex);
            auto fractionalPart = readIndex - integerPart;
            auto alpha = fractionalPart / (2.0 - fractionalPart);

            auto A = (integerPart + memorySize) % memorySize;
            auto B = (A + 1) % memorySize;

            for (int ch = 0; ch < numCh; ++ch)
            {
                // Input -> delay memory
                delayData[ch][writeIndex] = bufferData[ch][smp];

                // FRACTIONAL DELAY :: Interpolazione Allpass
                auto sampleValue = alpha * (delayData[ch][B] - oldSample[ch]) + delayData[ch][A];
                oldSample[ch] = sampleValue;

                // Delay memory -> buffer
                bufferData[ch][smp] = sampleValue;

                // Feedback
                delayData[ch][writeIndex] += sampleValue * fb;
            }

            ++writeIndex %= memorySize;
        }
    }

    void setDelayTime(double newValue)
    {
        delayTime.setTargetValue(newValue);
    }

    void setFeedback(float newValue)
    {
        feedback.setTargetValue(newValue);
    }

private:

    double sampleRate = 1.0;
    int memorySize = 0;
    int writeIndex = 0;

    float oldSample[2] = { 0.0, 0.0 };

    AudioBuffer<float> delayMemory;

    SmoothedValue<double, ValueSmoothingTypes::Linear> delayTime;
    SmoothedValue<float, ValueSmoothingTypes::Linear> feedback;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AnalogDelay)
};
