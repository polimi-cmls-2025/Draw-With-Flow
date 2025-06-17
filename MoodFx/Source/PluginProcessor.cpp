#include "PluginProcessor.h"
#include "PluginEditor.h"

MoodFXAudioProcessor::MoodFXAudioProcessor()
: parameters(*this, nullptr, "MoodFX", Parameters::createParameterLayout())
{
    Parameters::addListenerToAllParameters(parameters, this);
    
    muteAllEffects();
}

MoodFXAudioProcessor::~MoodFXAudioProcessor()
{
}

void MoodFXAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    chorus.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
    
    delay.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
    
    reverb.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
    
    overdrive.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
}

void MoodFXAudioProcessor::releaseResources()
{
    chorus.releaseResources();
    
    delay.releaseResources();
    
    reverb.releaseResources();
    
    overdrive.releaseResources();
}

void MoodFXAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    
    chorus.processBlock(buffer);
    
    delay.processBlock(buffer);
    
    reverb.processBlock(buffer);
    
    overdrive.processBlock(buffer);
}

juce::AudioProcessorEditor* MoodFXAudioProcessor::createEditor()
{
    return new PluginEditor (*this, parameters);
}

void MoodFXAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void MoodFXAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.replaceState(ValueTree::fromXml(*xmlState));
}

void MoodFXAudioProcessor::parameterChanged (const String& paramID, float newValue)
{
    // CHORUS
    
    if (paramID == Parameters::NAME_RATE)
        chorus.setRate(newValue);
    
    if (paramID == Parameters::NAME_INTENSITY)
    {
        newValue = jmap(newValue, Parameters::PERC_FLOOR, Parameters::PERC_CEILING, Parameters::INTENSITY_FLOOR, Parameters::INTENSITY_CEILING); // Mapping in the range [INTENSITY_FLOOR;INTENSITY_CEILING]
        chorus.setIntensity(newValue);
    }
    
    if (paramID == Parameters::NAME_STEREO_WIDTH)
    {
        newValue = jmap(newValue, Parameters::PERC_FLOOR, Parameters::PERC_CEILING, Parameters::STEREO_WIDTH_FLOOR, Parameters::STEREO_WIDTH_CEILING); // Mapping in the range [STEREO_WIDTH_FLOOR;STEREO_WIDTH_CEILING]
        chorus.setStereoWidth(newValue);
    }
    
    if (paramID == Parameters::NAME_AMOUNT)
    {
        newValue = jmap(newValue, Parameters::PERC_FLOOR, Parameters::PERC_CEILING, Parameters::AMOUNT_FLOOR, Parameters::AMOUNT_CEILING); // Mapping in the range [AMOUNT_FLOOR;AMOUNT_CEILING]
        chorus.setAmount(newValue);
    }
    
    if (paramID == Parameters::CHORUS_ACTIVE)
    {
        if (newValue > 0.5f)
        {
            chorus.setActive(true);
            
            delay.setActive(false);
            reverb.setActive(false);
            overdrive.setActive(false);
        }
        else
            chorus.setActive(false);
    }
    
    // DELAY
    
    if (paramID == Parameters::NAME_DELAY_TIME)
    {
        delay.setDelayTime(newValue);
    }
    
    if (paramID == Parameters::NAME_FEEDBACK)
    {
        newValue = jmap(newValue, Parameters::PERC_FLOOR, Parameters::PERC_CEILING, Parameters::FEEDBACK_FLOOR, Parameters::FEEDBACK_CEILING); // Mapping in the range [FEEDBACK_FLOOR;FEEDBACK_CEILING]
        delay.setFeedback(newValue);
    }
    
    if (paramID == Parameters::NAME_DELAY_DRY_WET)
    {
        newValue = jmap(newValue, Parameters::PERC_FLOOR, Parameters::PERC_CEILING, Parameters::AMOUNT_FLOOR, Parameters::AMOUNT_CEILING); // Mapping in the range [AMOUNT_FLOOR;AMOUNT_CEILING]
        delay.setDryWet(newValue);
    }
    
    if (paramID == Parameters::DELAY_ACTIVE)
    {
        if (newValue > 0.5f)
        {
            delay.setActive(true);
            
            chorus.setActive(false);
            reverb.setActive(false);
            overdrive.setActive(false);
        }
        else
            delay.setActive(false);
    }
    
    // REVERB
    
    if (paramID == Parameters::NAME_ROOM_SIZE)
    {
        newValue = jmap(newValue, Parameters::PERC_FLOOR, Parameters::PERC_CEILING, Parameters::ROOM_SIZE_FLOOR, Parameters::ROOM_SIZE_CEILING); // Mapping in the range [ROOM_SIZE_FLOOR;ROOM_SIZE_CEILING]
        reverb.setRoomSize(newValue);
    }
    
    if (paramID == Parameters::NAME_DAMPING)
    {
        newValue = jmap(newValue, Parameters::PERC_FLOOR, Parameters::PERC_CEILING, Parameters::DAMPING_FLOOR, Parameters::DAMPING_CEILING); // Mapping in the range [DAMPING_FLOOR;DAMPING_CEILING]
        reverb.setDamping(newValue);
    }
    
    if (paramID == Parameters::NAME_REVERB_WIDTH)
    {
        newValue = jmap(newValue, Parameters::PERC_FLOOR, Parameters::PERC_CEILING, Parameters::REVERB_WIDTH_FLOOR, Parameters::REVERB_WIDTH_CEILING); // Mapping in the range [REVERB_WIDTH_FLOOR;REVERB_WIDTH_CEILING]
        reverb.setWidth(newValue);
    }
    
    if (paramID == Parameters::NAME_REVERB_DRY_WET)
    {
        newValue = jmap(newValue, Parameters::PERC_FLOOR, Parameters::PERC_CEILING, Parameters::AMOUNT_FLOOR, Parameters::AMOUNT_CEILING); // Mapping in the range [AMOUNT_FLOOR;AMOUNT_CEILING]
        reverb.setDryWet(newValue);
    }
    
    if (paramID == Parameters::REVERB_ACTIVE)
    {
        if (newValue > 0.5f)
        {
            reverb.setActive(true);
            
            chorus.setActive(false);
            delay.setActive(false);
            overdrive.setActive(false);
        }
        else
            reverb.setActive(false);
    }
    
    // OVERDRIVE
    
    if (paramID == Parameters::NAME_GAIN)
    {
        newValue = Decibels::decibelsToGain(newValue);
        overdrive.setGain(newValue);
    }
    
    if (paramID == Parameters::NAME_TONE)
    {
        newValue = Decibels::decibelsToGain(newValue);
        overdrive.setTone(newValue, getSampleRate());
    }
    
    if (paramID == Parameters::NAME_OUTPUT_LEVEL)
    {
        newValue = Decibels::decibelsToGain(newValue);
        overdrive.setOutputLevel(newValue);
    }
    
    if (paramID == Parameters::OVERDRIVE_ACTIVE)
    {
        if (newValue > 0.5f)
        {
            overdrive.setActive(true);
            
            chorus.setActive(false);
            delay.setActive(false);
            reverb.setActive(false);
        }
        else
            overdrive.setActive(false);
    }
    
    // MOOD
    
    if (paramID == Parameters::NAME_MOOD)
    {
        currentMood = static_cast<int>(newValue);
        setMoodParameters();
    }
}

void MoodFXAudioProcessor::setParameterValue(juce::RangedAudioParameter *parameter, float value)
{
    parameter->beginChangeGesture();
    parameter->setValueNotifyingHost(value);
    parameter->endChangeGesture();
}

void MoodFXAudioProcessor::muteAllEffects()
{
    setParameterValue(parameters.getParameter(Parameters::CHORUS_ACTIVE), Parameters::DEFAULT_ACTIVE);
    setParameterValue(parameters.getParameter(Parameters::DELAY_ACTIVE), Parameters::DEFAULT_ACTIVE);
    setParameterValue(parameters.getParameter(Parameters::REVERB_ACTIVE), Parameters::DEFAULT_ACTIVE);
    setParameterValue(parameters.getParameter(Parameters::OVERDRIVE_ACTIVE), Parameters::DEFAULT_ACTIVE);
}

int MoodFXAudioProcessor::getCurrentMood() const
{
    return currentMood;
}

void MoodFXAudioProcessor::setMoodParameters ()
{
    // All effects off
    muteAllEffects();

    auto pluginParameters = getValueTreeState();

    switch (getCurrentMood())
    {
        case 0: // angry
        {
            // Declaring parameters
            auto gainParameter = pluginParameters->getParameter(Parameters::NAME_GAIN);
            auto toneParameter = pluginParameters->getParameter(Parameters::NAME_TONE);
            auto outputLevelParameter = pluginParameters->getParameter(Parameters::NAME_OUTPUT_LEVEL);

            // Mapping in the [0,1] range
            float gain0To1 = gainParameter->getNormalisableRange().convertTo0to1(Moods::preset_angry::GAIN); // map in [0,1] the gain
            float tone0To1 = toneParameter->getNormalisableRange().convertTo0to1(Moods::preset_angry::TONE); // map in [0,1] the tone
            float outputLevel0To1 = outputLevelParameter->getNormalisableRange().convertTo0to1(Moods::preset_angry::OUTPUT_LEVEL); // map in [0,1] the output level

            // Setting the parameters
            setParameterValue(gainParameter, gain0To1); // Set gain
            setParameterValue(toneParameter, tone0To1); // Set tone
            setParameterValue(outputLevelParameter, outputLevel0To1); // Set output level

            // Overdrive on
            setParameterValue(pluginParameters->getParameter(Parameters::OVERDRIVE_ACTIVE), Moods::EFFECT_STATUS);
        } break;

        case 1: // chill
        {
            // Declaring parameters
            auto roomSizeParameter = pluginParameters->getParameter(Parameters::NAME_ROOM_SIZE);
            auto dampingParameter = pluginParameters->getParameter(Parameters::NAME_DAMPING);
            auto widthParameter = pluginParameters->getParameter(Parameters::NAME_REVERB_WIDTH);
            auto dwRatioParameter = pluginParameters->getParameter(Parameters::NAME_REVERB_DRY_WET);

            // Mapping in the [0,1] range
            float roomSize0To1 = roomSizeParameter->getNormalisableRange().convertTo0to1(Moods::preset_chill::ROOM_SIZE);
            float damping0To1 = dampingParameter->getNormalisableRange().convertTo0to1(Moods::preset_chill::DAMPING);
            float width0To1 = widthParameter->getNormalisableRange().convertTo0to1(Moods::preset_chill::WIDTH);
            float dwRatio0To1 = dwRatioParameter->getNormalisableRange().convertTo0to1(Moods::preset_chill::DW_RATIO);

            // Setting reverb parameters
            setParameterValue(roomSizeParameter, roomSize0To1); // Set room size
            setParameterValue(dampingParameter, damping0To1); // Set damping
            setParameterValue(widthParameter, width0To1); // Set width
            setParameterValue(dwRatioParameter, dwRatio0To1); // Set dry/wet ratio

            // Reverb on
            setParameterValue(pluginParameters->getParameter(Parameters::REVERB_ACTIVE), Moods::EFFECT_STATUS);

        } break;

        case 2: // happy
        {
            // Declaring parameters
            auto rateParameter = pluginParameters->getParameter(Parameters::NAME_RATE);
            auto intensityParameter = pluginParameters->getParameter(Parameters::NAME_INTENSITY);
            auto stereoWidthParameter = pluginParameters->getParameter(Parameters::NAME_STEREO_WIDTH);
            auto amountParameter = pluginParameters->getParameter(Parameters::NAME_AMOUNT);

            // Mapping in the [0,1] range
            float rate0To1 = rateParameter->getNormalisableRange().convertTo0to1(Moods::preset_happy::RATE);
            float intensity0To1 = intensityParameter->getNormalisableRange().convertTo0to1(Moods::preset_happy::INTENSITY);
            float stereoWidth0To1 = stereoWidthParameter->getNormalisableRange().convertTo0to1(Moods::preset_happy::STEREO_WIDTH);
            float amount0To1 = amountParameter->getNormalisableRange().convertTo0to1(Moods::preset_happy::AMOUNT);

            // Setting chorus parameters
            setParameterValue(rateParameter, rate0To1); // Set rate
            setParameterValue(intensityParameter, intensity0To1); // Set intensity
            setParameterValue(stereoWidthParameter, stereoWidth0To1); // Set stereo width
            setParameterValue(amountParameter, amount0To1); // Set amount

            // Chorus on
            setParameterValue(pluginParameters->getParameter(Parameters::CHORUS_ACTIVE), Moods::EFFECT_STATUS);

        } break;

        case 3: // sad
        {
            // Declaring parameters
            auto delayTimeParameter = pluginParameters->getParameter(Parameters::NAME_DELAY_TIME);
            auto feedbackParameter = pluginParameters->getParameter(Parameters::NAME_FEEDBACK);
            auto dwRatioParameter = pluginParameters->getParameter(Parameters::NAME_DELAY_DRY_WET);

            // Mapping in the [0,1] range
            float delayTime0To1 = delayTimeParameter->getNormalisableRange().convertTo0to1(Moods::preset_sad::DELAY_TIME);
            float feedback0To1 = feedbackParameter->getNormalisableRange().convertTo0to1(Moods::preset_sad::FEEDBACK);
            float dwRatio0To1 = dwRatioParameter->getNormalisableRange().convertTo0to1(Moods::preset_sad::DW_RATIO);

            // Setting delay parameters
            setParameterValue(delayTimeParameter, delayTime0To1); // Set delay time
            setParameterValue(feedbackParameter, feedback0To1); // Set feedback
            setParameterValue(dwRatioParameter, dwRatio0To1); // Set dry/wet ratio

            // Delay on
            setParameterValue(pluginParameters->getParameter(Parameters::DELAY_ACTIVE), Moods::EFFECT_STATUS);
        } break;
    }
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MoodFXAudioProcessor();
}
