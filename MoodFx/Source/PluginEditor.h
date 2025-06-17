/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 7.0.12

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Parameters.h"
#include "GraphicTheme.h"

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PluginEditor  : public juce::AudioProcessorEditor,
                      public juce::Button::Listener,
                      public juce::Slider::Listener
{
public:
    //==============================================================================
    PluginEditor (MoodFXAudioProcessor& p, AudioProcessorValueTreeState& vts);
    ~PluginEditor() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void setMood ();

    void setAttachmentsForChorus();
    void setAttachmentsForDelay();
    void setAttachmentsForReverb();
    void setAttachmentsForOverdrive();

    void attachmentsReset ();

    void setGUIfor3Sliders (int mood);
    void setGUIfor4Sliders (int mood);
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    MoodFXAudioProcessor& processor;
    AudioProcessorValueTreeState& valueTreeState;

    // Mood slider attachment
    std::unique_ptr<SliderAttachment> moodAttachment;

    // Active button attachment
    std::unique_ptr<ButtonAttachment> statusAttachment;

    // Chorus sliders attachments
    std::unique_ptr<SliderAttachment> rateAttachment;
    std::unique_ptr<SliderAttachment> intensityAttachment;
    std::unique_ptr<SliderAttachment> amountAttachment;
    std::unique_ptr<SliderAttachment> stereoWidthAttachment;

    // Delay sliders attachments
    std::unique_ptr<SliderAttachment> delayTimeAttachment;
    std::unique_ptr<SliderAttachment> feedbackAttachment;
    std::unique_ptr<SliderAttachment> delayDryWetAttachment;

    // Reverb sliders attachments
    std::unique_ptr<SliderAttachment> roomSizeAttachment;
    std::unique_ptr<SliderAttachment> dampingAttachment;
    std::unique_ptr<SliderAttachment> widthAttachment;
    std::unique_ptr<SliderAttachment> reverbDryWetAttachment;

    // Overdrive sliders attachments
    std::unique_ptr<SliderAttachment> gainAttachment;
    std::unique_ptr<SliderAttachment> toneAttachment;
    std::unique_ptr<SliderAttachment> outputLvlAttachment;

    // LookAndFeels
    ToggleButtonTheme toggleButtonTheme;
    SliderTheme sliderTheme;
    SliderTheme moodSliderTheme;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<CustomSlider> slider1;
    std::unique_ptr<CustomSlider> slider2;
    std::unique_ptr<CustomSlider> slider4;
    std::unique_ptr<CustomToggleButton> effectStatus;
    std::unique_ptr<CustomSlider> slider3;
    std::unique_ptr<juce::Label> sl1Label;
    std::unique_ptr<juce::Label> sl2Label;
    std::unique_ptr<juce::Label> sl3Label;
    std::unique_ptr<juce::Label> sl4Label;
    std::unique_ptr<CustomSlider> moodSlider;
    std::unique_ptr<juce::Label> moodSelectorLabel;
    std::unique_ptr<juce::Label> effectLabel;
    std::unique_ptr<juce::Label> onOffLabel;
    std::unique_ptr<juce::Label> nameLabel;
    std::unique_ptr<juce::Label> fxLabel;
    std::unique_ptr<juce::Label> byLabel;
    std::unique_ptr<juce::Label> effectSetupLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

