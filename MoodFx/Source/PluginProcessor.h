#pragma once
#include <JuceHeader.h>
#include "Effects.h"

enum Mood { angry, chill, happy, sad };

class MoodFXAudioProcessor  : public juce::AudioProcessor, public AudioProcessorValueTreeState::Listener
{
public:
    MoodFXAudioProcessor();
    ~MoodFXAudioProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; };

    const juce::String getName() const override { return JucePlugin_Name; };

    bool acceptsMidi() const override { return false; };
    bool producesMidi() const override { return false; };
    bool isMidiEffect() const override { return false; };
    double getTailLengthSeconds() const override { return 0.0; };
    int getNumPrograms() override { return 1; };
    int getCurrentProgram() override { return 0; };
    void setCurrentProgram (int index) override {};
    const juce::String getProgramName (int index) override { return {};  };
    void changeProgramName (int index, const juce::String& newName) override {};
 
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    AudioProcessorValueTreeState* getValueTreeState () { return &parameters; };
    
    void setParameterValue(juce::RangedAudioParameter *parameter, float value);
    
    void muteAllEffects ();
    
    int getCurrentMood() const ;
    
    void setMoodParameters();
    
private:
    void parameterChanged (const String& paramID, float newValue) override;
    AudioProcessorValueTreeState parameters;
    int currentMood = 0;
    
    // Chorus
    Effects::Chorus chorus;
    
    // Delay
    Effects::Delay delay;
    
    // Overdrive
    Effects::Overdrive overdrive;
    
    // Reverb
    Effects::Reverb reverb;
        
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MoodFXAudioProcessor)
};
