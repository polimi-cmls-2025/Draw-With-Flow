#pragma once
#include <JuceHeader.h>
#include "Parameters.h"

class Mixer
{
public:
    Mixer() {}
    
    ~Mixer() {}
    
    void prepareToPlay (const double sampleRate, const int maxNumSamples, const int actualNumChannels)
    {
        numChannels = actualNumChannels;
        
        drySignal.setSize(numChannels, maxNumSamples);
        drySignal.clear();
        
        dryLvl.reset(sampleRate, Parameters::SMOOTHING_TIME);
        wetLvl.reset(sampleRate, Parameters::SMOOTHING_TIME);
        
        updateInternalState();
    }
    
    void releaseResources()
    {
        drySignal.setSize(0, 0);
        numChannels = 0;
    }
    
    void copyDrySignal (AudioBuffer<float>& buffer)
    {
        const auto numSamples = buffer.getNumSamples();

        for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
            drySignal.copyFrom(ch, 0, buffer, ch, 0, numSamples);
    }

    void merge (AudioBuffer<float>& buffer)
    {
        const auto numSamples = buffer.getNumSamples();

        wetLvl.applyGain(buffer, numSamples);
        dryLvl.applyGain(drySignal, numSamples);

        for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
            buffer.addFrom(ch, 0, drySignal, ch, 0, numSamples);
    }
    
    void setDryWetRatio (const float newValue)
    {
        dryWetRatio = newValue;
        updateInternalState();
    }
    
    void setActive (bool newValue)
    {
        active = newValue;
        updateInternalState();
    }
    
private:
    void updateInternalState ()
    {
        if (active)
        {
            dryLvl.setTargetValue(sqrt(1 - dryWetRatio));
            wetLvl.setTargetValue(sqrt(dryWetRatio));
        }
        else
        {
            dryLvl.setTargetValue(1.0f);
            wetLvl.setTargetValue(0.0f);
        }
    }
    
    int numChannels = 2;
    
    AudioBuffer<float> drySignal;
    bool active;
    
    float dryWetRatio = Parameters::DEFAULT_DW_RATIO;
    
    SmoothedValue<float, ValueSmoothingTypes::Linear> dryLvl;
    SmoothedValue<float, ValueSmoothingTypes::Linear> wetLvl;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Mixer)
};

