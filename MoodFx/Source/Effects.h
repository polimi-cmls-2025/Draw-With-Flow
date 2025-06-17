#pragma once
#include "Delay.h"
#include "Mixer.h"
#include "Oscillator.h"

namespace Effects {

constexpr bool CLASS_DEFAULT_ACTIVE         = true;

// Class that implements a chorus effect with:
// an LFO of the class Oscillator
// a delay module of the class ModDelay
// an intensity regulator of the class ParameterModulation
constexpr float CLASS_DEFAULT_RATE          = 1.0f; // 1 Hz
constexpr float CLASS_DEFAULT_INTENSITY     = 0.0f;
constexpr float CLASS_DEFAULT_AMOUNT        = 0.5f;
constexpr float CLASS_DEFAULT_STEREO_WIDTH  = 0.5f;

constexpr float CHORUS_FEEDBACK             = 0.0f;

class Chorus
{
    public:
    
    Chorus (float def_rate = CLASS_DEFAULT_RATE, float def_intensity = CLASS_DEFAULT_INTENSITY, float def_amount = CLASS_DEFAULT_AMOUNT, float def_st_width = CLASS_DEFAULT_STEREO_WIDTH, bool def_active = CLASS_DEFAULT_ACTIVE)
    {
        delay.setFeedback(CHORUS_FEEDBACK);
        
        lfo.setFrequency(def_rate);
        intensityRegulator.setModulationAmount(def_intensity * 0.001);
        amounter.setDryWetRatio(def_amount);
        lfo.setPhaseDelta(def_st_width);
        
        amounter.setActive(def_active);
    }
    
    ~Chorus() {}
    
    void setActive (bool currentStatus)
    {
        amounter.setActive(currentStatus);
    }
    
    void setAmount (float newValue)
    {
        amounter.setDryWetRatio(newValue);
    }
    
    void setIntensity (float newValue)
    {
        intensityRegulator.setModulationAmount(newValue * 0.001);
    }
    
    void setRate (float newValue)
    {
        lfo.setFrequency(newValue);
    }
    
    void setStereoWidth (float newValue)
    {
        lfo.setPhaseDelta(newValue);
    }
    
    void prepareToPlay (double sampleRate, int samplesPerBlock, int numChannels)
    {
        amounter.prepareToPlay(sampleRate, samplesPerBlock, numChannels);
        delay.prepareToPlay(sampleRate, samplesPerBlock);
        lfo.prepareToPlay(sampleRate);
        intensityRegulator.prepareToPlay(sampleRate);
        delayModulation.setSize(2, samplesPerBlock);
        delayModulation.clear();
    }
    
    void releaseResources()
    {
        amounter.releaseResources();
        delay.releaseResources();
    }
    
    void processBlock (juce::AudioBuffer<float>& buffer)
    {
        const auto numSamples = buffer.getNumSamples();
        
        lfo.getNextAudioBlock(delayModulation, numSamples);
        intensityRegulator.processBlock(delayModulation, numSamples);
        
        amounter.copyDrySignal(buffer);
        
        delay.processBlock(buffer, delayModulation);
        
        amounter.merge(buffer);
    }
    
    private:
    
    Mixer amounter;
    Oscillator lfo;
    ParameterModulation intensityRegulator;
    ModDelay delay;
    
    AudioBuffer<double> delayModulation;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Chorus)
};

// Class that implements a feedback delay by using the Analog delay and Mixer
// for the dry/wet functionality
constexpr float CLASS_DEFAULT_DELAY_TIME    = 1.0f;
constexpr float CLASS_DEFAULT_FEEDBACK      = 0.0f;
constexpr float CLASS_DEFAULT_DW_RATIO      = 0.25f;

class Delay
{
    public:
    
    Delay (float def_d_time = CLASS_DEFAULT_DELAY_TIME, float def_feedback = CLASS_DEFAULT_FEEDBACK, float def_dw_ratio = CLASS_DEFAULT_DW_RATIO, bool def_active = CLASS_DEFAULT_ACTIVE)
    {
        delay.setDelayTime(def_d_time);
        delay.setFeedback(def_feedback);
        dryWetter.setDryWetRatio(def_dw_ratio);
        dryWetter.setActive(def_active);
    }
    
    void setActive (bool currentStatus)
    {
        dryWetter.setActive(currentStatus);
    }
    
    void setDelayTime (float newValue)
    {
        delay.setDelayTime(newValue);
    }
    
    void setFeedback (float newValue)
    {
        delay.setFeedback(newValue);
    }
    
    void setDryWet (float newValue)
    {
        dryWetter.setDryWetRatio(newValue);
    }
    
    void prepareToPlay (double sampleRate, int samplesPerBlock, int numChannels)
    {
        dryWetter.prepareToPlay(sampleRate, samplesPerBlock, numChannels);
        delay.prepareToPlay(sampleRate, samplesPerBlock);
    }
    
    void releaseResources()
    {
        dryWetter.releaseResources();
        delay.releaseResources();
    }
    
    void processBlock (juce::AudioBuffer<float>& buffer)
    {
        dryWetter.copyDrySignal(buffer);
        delay.processBlock(buffer);
        dryWetter.merge(buffer);
    }
    
    private:
    
    AnalogDelay delay;
    Mixer dryWetter;
};


// Class that implements a simple reverb based on the juce::Reverb class
constexpr float CLASS_DEFAULT_ROOM_SIZE     = 0.1f;
constexpr float CLASS_DEFAULT_DAMPING       = 0.5f;
constexpr float CLASS_DEFAULT_WIDTH         = 0.5f;

class Reverb
{
    public:
    Reverb(float def_r_size = CLASS_DEFAULT_ROOM_SIZE, float def_damping = CLASS_DEFAULT_DAMPING, float def_width = CLASS_DEFAULT_WIDTH, float def_dw_ratio = CLASS_DEFAULT_DW_RATIO, bool def_active = CLASS_DEFAULT_ACTIVE)
    {
        params.dryLevel = 0.0f;
        params.wetLevel = 1.0f; // only wet level (dry/wet functionality implemented by Mixer class)
        
        params.roomSize = def_r_size;
        params.damping = def_damping;
        params.width = def_width;
        
        reverb.setParameters(params);
        
        dryWetter.setDryWetRatio(def_dw_ratio);
        dryWetter.setActive(def_active);
    }
    
    ~Reverb() {}
    
    void setActive(bool currentStatus)
    {
        dryWetter.setActive(currentStatus);
    }
    
    void setDamping(float newValue)
    {
        params.damping = newValue;
        reverb.setParameters(params);
    }
    
    void setDryWet(float newValue)
    {
        dryWetter.setDryWetRatio(newValue);
    }
    
    void setRoomSize(float newValue)
    {
        params.roomSize = newValue;
        reverb.setParameters(params);
    }
    
    void setWidth(float newValue)
    {
        params.width = newValue;
        reverb.setParameters(params);
    }
    
    void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels)
    {
        dryWetter.prepareToPlay(sampleRate, samplesPerBlock, numChannels);
        reverb.setSampleRate(sampleRate);
    }
    
    void releaseResources()
    {
        dryWetter.releaseResources();
    }
    
    void processBlock(juce::AudioBuffer<float>& buffer)
    {
        dryWetter.copyDrySignal(buffer);
        reverb.processStereo(buffer.getWritePointer(0), buffer.getWritePointer(1), buffer.getNumSamples());
        dryWetter.merge(buffer);
    }
    
    private:
    
    juce::Reverb reverb;
    juce::Reverb::Parameters params;
    Mixer dryWetter;
    
};


// Class that implements a distortion effect based on three parameters
// a gain, a tone and an output volume

constexpr float CLASS_DEFAULT_GAIN          = 1.0f; // Linear gain value
constexpr float CLASS_DEFAULT_TONE          = 1.0f; // Linear tone value
constexpr float CLASS_DEFAULT_OUTPUT_LEVEL  = 1.0f; // Linear output level value

class Overdrive
{
    public:
    
    Overdrive (float def_gain = CLASS_DEFAULT_GAIN, float def_tone = CLASS_DEFAULT_TONE, float def_outputlvl = CLASS_DEFAULT_OUTPUT_LEVEL, bool def_active = CLASS_DEFAULT_ACTIVE)
    {
        gain.setTargetValue(def_gain);
        tone.setTargetValue(def_tone);
        outputLevel.setTargetValue(def_outputlvl);
        active = def_active;
    }
    
    void setActive (bool currentStatus)
    {
        active = currentStatus;
    }
    
    void setGain (float newValue)
    {
        gain.setTargetValue(newValue);
    }
    
    void setTone (float newValue, double sampleRate)
    {
        tone.setTargetValue(newValue);
        
        updateFilterCoefficients(sampleRate);
    }
    
    void setOutputLevel (float newValue)
    {
        outputLevel.setTargetValue(newValue);
    }
    
    void prepareToPlay (double sampleRate, int samplesPerBlock, int numChannels)
    {
        gain.getNextValue();
        tone.getNextValue();
        outputLevel.getNextValue();
        
        juce::dsp::ProcessSpec spec;
        spec.sampleRate = sampleRate;
        spec.maximumBlockSize = samplesPerBlock;
        spec.numChannels = numChannels;
        
        toneProcessors.resize(numChannels);
        for (auto& filter : toneProcessors)
            filter.prepare(spec);
    }
    
    void releaseResources ()
    {
        toneProcessors.resize(0);
    }
    
    float processSample (float inputSample)
    {
        float outputSample;
        
        // Applying the distortion transfer function
        if (abs(inputSample) < 1.0f)
            outputSample = inputSample - (1.0f / 3.0f) * pow(inputSample, 3);
        else
            outputSample = (inputSample > 0.0f) ? 2.0f / 3.0f : -2.0f / 3.0f;
        
        return outputSample;
    }
    
    void processChannel (float* bufferData, int numSamples)
    {
        for (int smp = 0; smp < numSamples; ++smp)
            bufferData[smp] = processSample(bufferData[smp]);
    }
    
    void processBlock (juce::AudioBuffer<float>& buffer)
    {
        if (!active)
            return;
        
        auto numChannels = buffer.getNumChannels();
        auto numSamples = buffer.getNumSamples();
    
        buffer.applyGain(gain.getNextValue()); // Gain applies to the entire buffer in the process block
        
        // Applying distortion & tone control
        auto bufferData = buffer.getArrayOfWritePointers();
        for (int ch = 0; ch < numChannels; ++ ch)
        {
            processChannel(bufferData[ch], numSamples);
            
            juce::dsp::AudioBlock<float> channelBlock(buffer);
            auto singleChannel = channelBlock.getSingleChannelBlock(ch);
            juce::dsp::ProcessContextReplacing<float> context(singleChannel);
            toneProcessors[ch].process(context);
        }
         
        buffer.applyGain(outputLevel.getNextValue()); // Output level applies to the entire buffer at the end of the processing
    }
    
    private:
    
    void updateFilterCoefficients (double sampleRate)
    {
        auto coefficients = juce::dsp::IIR::Coefficients<float>::makeHighShelf(sampleRate, Parameters::TONE_FREQUENCY, Parameters::TONE_Q_FACTOR, tone.getCurrentValue());
        
        for (auto& filter : toneProcessors)
            filter.coefficients = coefficients;
    }
    
    SmoothedValue<double, ValueSmoothingTypes::Linear> gain;
    SmoothedValue<double, ValueSmoothingTypes::Linear> tone;
    SmoothedValue<double, ValueSmoothingTypes::Linear> outputLevel;
    
    bool active;
    
    // Highshelf (baxandall tone control)
    std::vector<juce::dsp::IIR::Filter<float>> toneProcessors;
};

}
