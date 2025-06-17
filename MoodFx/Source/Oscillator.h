#pragma once
#include <JuceHeader.h>
#include "Parameters.h"

// Oscillator is a class that implements an LFO that generates a stereo sine
// wave with a frequency between 0.1 and 25 Hz and a phase delta (between 0.0
// and 1.0) between the two channels.
// A phase delta of 0.5 represents a sine wave shifted by half of its period.
class Oscillator
{
public:
    Oscillator ()
    {
        frequency.setCurrentAndTargetValue(Parameters::DEFAULT_RATE);
        phaseDelta.setCurrentAndTargetValue(Parameters::DEFAULT_STEREO_WIDTH);
    }
    
    ~Oscillator ()
    {
    }
    
    void prepareToPlay (const double sampleRate)
    {
        samplePeriod = 1.0 / sampleRate;
        frequency.reset(sampleRate, Parameters::LFO_RAMP_LENGTH);
        phaseDelta.reset(sampleRate, Parameters::LFO_RAMP_LENGTH);
    }
    
    void setFrequency (const double newValue)
    {
        frequency.setTargetValue(newValue);
    }
    
    void setPhaseDelta (const double newValue)
    {
        phaseDelta.setTargetValue(newValue);
    }
    
    void getNextAudioBlock (AudioBuffer<double>& buffer, const int numSamples)
    {
        auto bufferData = buffer.getArrayOfWritePointers();
        
        for (int smp = 0; smp < numSamples; ++smp)
        {
            auto leftSample = 0.0f;
            auto rightSample = 0.0f;
            getNextAudioSample(&leftSample, &rightSample);
            
            bufferData[0][smp] = leftSample;
            bufferData[1][smp] = rightSample;
        }
    }
    
    void getNextAudioSample (float *leftSample, float *rightSample)
    {
        auto leftPhase = currentPhase;
        auto rightPhase = currentPhase + phaseDelta.getNextValue();
        rightPhase -= static_cast<int>(rightPhase);
        
        *leftSample = sin(MathConstants<float>::twoPi * leftPhase);
        *rightSample = sin(MathConstants<float>::twoPi * rightPhase);
        
        phaseIncrement = frequency.getNextValue() * samplePeriod; 
        currentPhase += phaseIncrement;
        currentPhase -= static_cast<int>(currentPhase);
    }
    
private:
    
    double samplePeriod = 1.0;
    double currentPhase = 0.0;
    double phaseIncrement = 0.0;
    
    SmoothedValue<double, ValueSmoothingTypes::Multiplicative> frequency;
    SmoothedValue<double, ValueSmoothingTypes::Linear> phaseDelta;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};

// The class ParameterModulation implements a time-controller for an audio
// parameter based on an LFO.
class ParameterModulation
{
public:
    ParameterModulation ()
    {
        modulationAmount.setCurrentAndTargetValue(0.0);
        parameter.setCurrentAndTargetValue(Parameters::CHORUS_DELAY_TIME);
    }
    
    ~ParameterModulation ()
    {
    }
    
    void prepareToPlay (const double sampleRate)
    {
        modulationAmount.reset(sampleRate, Parameters::MA_RAMP_LENGTH);
        parameter.reset(sampleRate, Parameters::PAR_RAMP_LENGTH);
    }
    
    void setModulationAmount (const double newValue)
    {
        modulationAmount.setTargetValue(newValue);
    }
    
    void processBlock (AudioBuffer<double>& buffer, const int numSamples)
    {
        auto bufferData = buffer.getArrayOfWritePointers();
        auto numChannels = buffer.getNumChannels();
        
        // Sinewave shifting of +1 and halved on the plane
        for (int ch = 0; ch < numChannels; ++ch)
        {
            FloatVectorOperations::add(bufferData[ch], 1.0, numSamples);
            FloatVectorOperations::multiply(bufferData[ch], 0.5, numSamples);
        }
        
        modulationAmount.applyGain(buffer, numSamples);
        
        for (int smp = 0; smp < numSamples; ++smp)
        {
            for (int ch = 0; ch < numChannels; ++ch)
            {
                bufferData[ch][smp] += ch ? parameter.getCurrentValue() : parameter.getNextValue();
            }
        }
        
        for (int ch = 0; ch < numChannels; ++ch)
        {
            FloatVectorOperations::min(bufferData[ch], bufferData[ch], Parameters::MAX_DELAY_TIME, numSamples);
        }
    }
    
private:
    
    SmoothedValue<double, ValueSmoothingTypes::Linear> modulationAmount;
    SmoothedValue<double, ValueSmoothingTypes::Linear> parameter;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParameterModulation)
};


