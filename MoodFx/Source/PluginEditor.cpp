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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
constexpr static int OFFSET     = 78;
//[/MiscUserDefs]

//==============================================================================
PluginEditor::PluginEditor (MoodFXAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p), valueTreeState (vts)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    slider1.reset (new CustomSlider ("Slider 1"));
    addAndMakeVisible (slider1.get());
    slider1->setRange (0, 10, 0);
    slider1->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    slider1->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    slider1->setColour (juce::Slider::textBoxTextColourId, juce::Colour (0xff3e3e3e));
    slider1->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x408e989b));

    slider1->setBounds (388, 88, 110, 110);

    slider2.reset (new CustomSlider ("Slider 2"));
    addAndMakeVisible (slider2.get());
    slider2->setRange (0, 10, 0);
    slider2->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    slider2->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    slider2->setColour (juce::Slider::textBoxTextColourId, juce::Colour (0xff3e3e3e));
    slider2->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x408e989b));

    slider2->setBounds (543, 88, 110, 110);

    slider4.reset (new CustomSlider ("Slider 4"));
    addAndMakeVisible (slider4.get());
    slider4->setRange (0, 10, 0);
    slider4->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    slider4->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    slider4->setColour (juce::Slider::textBoxTextColourId, juce::Colour (0xff3e3e3e));
    slider4->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x408e989b));

    slider4->setBounds (543, 256, 110, 110);

    effectStatus.reset (new CustomToggleButton ("Active"));
    addAndMakeVisible (effectStatus.get());
    effectStatus->setButtonText (juce::String());
    effectStatus->addListener (this);

    effectStatus->setBounds (506, 394, 37, 26);

    slider3.reset (new CustomSlider ("Slider 3"));
    addAndMakeVisible (slider3.get());
    slider3->setRange (0, 10, 0);
    slider3->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    slider3->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    slider3->setColour (juce::Slider::textBoxTextColourId, juce::Colour (0xff3e3e3e));
    slider3->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x408e989b));

    slider3->setBounds (388, 256, 110, 110);

    sl1Label.reset (new juce::Label ("Slider 1 label",
                                     TRANS ("slider 1 label")));
    addAndMakeVisible (sl1Label.get());
    sl1Label->setFont (juce::Font ("Rajdhani", 20.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    sl1Label->setJustificationType (juce::Justification::centred);
    sl1Label->setEditable (false, false, false);
    sl1Label->setColour (juce::Label::textColourId, juce::Colour (0xff3e3e3e));
    sl1Label->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    sl1Label->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    sl1Label->setBounds (383, 61, 120, 24);

    sl2Label.reset (new juce::Label ("Slider 2 label",
                                     TRANS ("slider 2 label")));
    addAndMakeVisible (sl2Label.get());
    sl2Label->setFont (juce::Font ("Rajdhani", 20.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    sl2Label->setJustificationType (juce::Justification::centred);
    sl2Label->setEditable (false, false, false);
    sl2Label->setColour (juce::Label::textColourId, juce::Colour (0xff3e3e3e));
    sl2Label->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    sl2Label->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    sl2Label->setBounds (538, 61, 120, 24);

    sl3Label.reset (new juce::Label ("Slider 3 label",
                                     TRANS ("slider 3 label")));
    addAndMakeVisible (sl3Label.get());
    sl3Label->setFont (juce::Font ("Rajdhani", 20.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    sl3Label->setJustificationType (juce::Justification::centred);
    sl3Label->setEditable (false, false, false);
    sl3Label->setColour (juce::Label::textColourId, juce::Colour (0xff3e3e3e));
    sl3Label->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    sl3Label->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    sl3Label->setBounds (383, 229, 120, 24);

    sl4Label.reset (new juce::Label ("Slider 4 label",
                                     TRANS ("slider 4 label")));
    addAndMakeVisible (sl4Label.get());
    sl4Label->setFont (juce::Font ("Rajdhani", 20.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    sl4Label->setJustificationType (juce::Justification::centred);
    sl4Label->setEditable (false, false, false);
    sl4Label->setColour (juce::Label::textColourId, juce::Colour (0xff3e3e3e));
    sl4Label->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    sl4Label->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    sl4Label->setBounds (538, 229, 120, 24);

    moodSlider.reset (new CustomSlider ("Mood Slider"));
    addAndMakeVisible (moodSlider.get());
    moodSlider->setRange (0, 10, 0);
    moodSlider->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    moodSlider->setTextBoxStyle (juce::Slider::NoTextBox, true, 80, 20);
    moodSlider->setColour (juce::Slider::textBoxTextColourId, juce::Colours::black);
    moodSlider->setColour (juce::Slider::textBoxOutlineColourId, juce::Colour (0x008e989b));
    moodSlider->addListener (this);

    moodSlider->setBounds (110, 145, 130, 130);

    moodSelectorLabel.reset (new juce::Label ("Mood selector label",
                                              TRANS ("MOOD SELECTOR\n")));
    addAndMakeVisible (moodSelectorLabel.get());
    moodSelectorLabel->setFont (juce::Font ("Rajdhani", 20.00f, juce::Font::plain).withTypefaceStyle ("Medium"));
    moodSelectorLabel->setJustificationType (juce::Justification::centred);
    moodSelectorLabel->setEditable (false, false, false);
    moodSelectorLabel->setColour (juce::Label::textColourId, juce::Colour (0xff3e3e3e));
    moodSelectorLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    moodSelectorLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    moodSelectorLabel->setBounds (115, 305, 120, 24);

    effectLabel.reset (new juce::Label ("Effect label",
                                        TRANS ("slider 3 label")));
    addAndMakeVisible (effectLabel.get());
    effectLabel->setFont (juce::Font ("Rajdhani", 20.00f, juce::Font::plain).withTypefaceStyle ("Medium"));
    effectLabel->setJustificationType (juce::Justification::centredRight);
    effectLabel->setEditable (false, false, false);
    effectLabel->setColour (juce::Label::textColourId, juce::Colour (0xff3e3e3e));
    effectLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    effectLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    effectLabel->setBounds (377, 395, 114, 24);

    onOffLabel.reset (new juce::Label ("ON/OFF label",
                                       TRANS ("ON/OFF")));
    addAndMakeVisible (onOffLabel.get());
    onOffLabel->setFont (juce::Font ("Rajdhani", 20.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    onOffLabel->setJustificationType (juce::Justification::centred);
    onOffLabel->setEditable (false, false, false);
    onOffLabel->setColour (juce::Label::textColourId, juce::Colour (0xff3e3e3e));
    onOffLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    onOffLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    onOffLabel->setBounds (554, 395, 56, 24);

    nameLabel.reset (new juce::Label ("Mood",
                                      TRANS ("Mood")));
    addAndMakeVisible (nameLabel.get());
    nameLabel->setFont (juce::Font ("Rajdhani", 40.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    nameLabel->setJustificationType (juce::Justification::centred);
    nameLabel->setEditable (false, false, false);
    nameLabel->setColour (juce::Label::textColourId, juce::Colour (0xff3e3e3e));
    nameLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    nameLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    nameLabel->setBounds (88, 49, 78, 39);

    fxLabel.reset (new juce::Label ("Name",
                                    TRANS ("FX\n")));
    addAndMakeVisible (fxLabel.get());
    fxLabel->setFont (juce::Font ("Rajdhani", 40.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    fxLabel->setJustificationType (juce::Justification::centred);
    fxLabel->setEditable (false, false, false);
    fxLabel->setColour (juce::Label::textColourId, juce::Colour (0xff3e3e3e));
    fxLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    fxLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    fxLabel->setBounds (140, 49, 78, 39);

    byLabel.reset (new juce::Label ("by BIME",
                                    TRANS ("by BIME")));
    addAndMakeVisible (byLabel.get());
    byLabel->setFont (juce::Font ("Rajdhani", 20.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    byLabel->setJustificationType (juce::Justification::centred);
    byLabel->setEditable (false, false, false);
    byLabel->setColour (juce::Label::textColourId, juce::Colour (0xff3e3e3e));
    byLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    byLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    byLabel->setBounds (192, 54, 78, 39);

    effectSetupLabel.reset (new juce::Label ("Effect setup",
                                             TRANS ("EFFECT SETUP\n")));
    addAndMakeVisible (effectSetupLabel.get());
    effectSetupLabel->setFont (juce::Font ("Rajdhani", 20.00f, juce::Font::plain).withTypefaceStyle ("Medium"));
    effectSetupLabel->setJustificationType (juce::Justification::centred);
    effectSetupLabel->setEditable (false, false, false);
    effectSetupLabel->setColour (juce::Label::textColourId, juce::Colour (0xff3e3e3e));
    effectSetupLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    effectSetupLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    effectSetupLabel->setBounds (471, 10, 100, 39);


    //[UserPreSize]
    moodAttachment.reset(new SliderAttachment(valueTreeState, Parameters::NAME_MOOD, *moodSlider));

    switch (processor.getCurrentMood())
    {
        case 0:
        {
            setAttachmentsForOverdrive();
            setGUIfor3Sliders(0);
        } break;

        case 1:
        {
            setAttachmentsForReverb();
            setGUIfor4Sliders(1);
        } break;

        case 2:
        {
            setAttachmentsForChorus();
            setGUIfor4Sliders(2);
        }

        case 3:
        {
            setAttachmentsForDelay();
            setGUIfor3Sliders(3);
        } break;
    }

    effectStatus->setLookAndFeel(&toggleButtonTheme);

    toggleButtonTheme.setMood(processor.getCurrentMood());

    moodSliderTheme.setMood(4);
    moodSlider->setLookAndFeel(&moodSliderTheme);
    moodSliderTheme.attachProcessor(&processor);

    sliderTheme.setMood(processor.getCurrentMood());

    slider1->setLookAndFeel(&sliderTheme);
    slider2->setLookAndFeel(&sliderTheme);
    slider3->setLookAndFeel(&sliderTheme);
    slider4->setLookAndFeel(&sliderTheme);

    if (effectStatus->getToggleState())
    {
        juce::Colour labelColour;
        switch (processor.getCurrentMood())
        {
            case 0: labelColour = juce::Colour(OVERDRIVE_COLOUR); break;
            case 1: labelColour = juce::Colour(REVERB_COLOUR); break;
            case 2: labelColour = juce::Colour(CHORUS_COLOUR); break;
            case 3: labelColour = juce::Colour(DELAY_COLOUR); break;
        }
        fxLabel->setColour (juce::Label::textColourId, labelColour);
    }
    else
    {
        sliderTheme.setMood(-1);
        fxLabel->setColour (juce::Label::textColourId, juce::Colour(GRAY_COLOUR));

        slider1->repaint();
        slider2->repaint();
        slider3->repaint();
        slider4->repaint();
    }
    //[/UserPreSize]

    setSize (710, 450);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

PluginEditor::~PluginEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    moodAttachment.reset();
    attachmentsReset();
    //[/Destructor_pre]

    slider1 = nullptr;
    slider2 = nullptr;
    slider4 = nullptr;
    effectStatus = nullptr;
    slider3 = nullptr;
    sl1Label = nullptr;
    sl2Label = nullptr;
    sl3Label = nullptr;
    sl4Label = nullptr;
    moodSlider = nullptr;
    moodSelectorLabel = nullptr;
    effectLabel = nullptr;
    onOffLabel = nullptr;
    nameLabel = nullptr;
    fxLabel = nullptr;
    byLabel = nullptr;
    effectSetupLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PluginEditor::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xffebebeb));

    {
        float x = 10.0f, y = 10.0f, width = 690.0f, height = 430.0f;
        juce::Colour fillColour = juce::Colour (0x10525252);
        juce::Colour strokeColour = juce::Colour (0xff3e3e3e);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 10.000f, 1.500f);
    }

    {
        int x = 340, y = 50, width = 1, height = 350;
        juce::Colour strokeColour = juce::Colour (0xff3e3e3e);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 1);

    }

    {
        int x = 35, y = 343, width = 280, height = 30;
        juce::String text (TRANS ("Let your mood choose the sound."));
        juce::Colour fillColour = juce::Colour (0xff3e3e3e);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Rajdhani", 16.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 68, y = 262, width = 64, height = 30;
        juce::String text (TRANS ("ANGRY"));
        juce::Colour fillColour = juce::Colour (0xff3e3e3e);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Rajdhani", 15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredRight, true);
    }

    {
        int x = 220, y = 262, width = 64, height = 30;
        juce::String text (TRANS ("SAD"));
        juce::Colour fillColour = juce::Colour (0xff3e3e3e);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Rajdhani", 15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    {
        int x = 55, y = 141, width = 64, height = 30;
        juce::String text (TRANS ("CHILL"));
        juce::Colour fillColour = juce::Colour (0xff3e3e3e);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Rajdhani", 15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredRight, true);
    }

    {
        int x = 231, y = 141, width = 64, height = 30;
        juce::String text (TRANS ("HAPPY"));
        juce::Colour fillColour = juce::Colour (0xff3e3e3e);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Rajdhani", 15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centredLeft, true);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PluginEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void PluginEditor::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == effectStatus.get())
    {
        //[UserButtonCode_effectStatus] -- add your button handler code here..

        // If the effect is off every sliders become gray
        if (effectStatus->getToggleState())
        {
            sliderTheme.setMood(processor.getCurrentMood());
            juce::Colour labelColour;
            switch (static_cast<int>(processor.getCurrentMood()))
            {
                case 0: labelColour = juce::Colour(OVERDRIVE_COLOUR); break;
                case 1: labelColour = juce::Colour(REVERB_COLOUR); break;
                case 2: labelColour = juce::Colour(CHORUS_COLOUR); break;
                case 3: labelColour = juce::Colour(DELAY_COLOUR); break;
            }
            fxLabel->setColour (juce::Label::textColourId, labelColour);
        }
        else
        {
            sliderTheme.setMood(-1);
            fxLabel->setColour (juce::Label::textColourId, juce::Colour(GRAY_COLOUR));
        }

        slider1->repaint();
        slider2->repaint();
        slider3->repaint();
        slider4->repaint();


        //[/UserButtonCode_effectStatus]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void PluginEditor::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == moodSlider.get())
    {
        //[UserSliderCode_moodSlider] -- add your slider handling code here..
        auto currMood = sliderThatWasMoved->getValue();

        if (currMood == 0 || currMood == 3)
        {
            if (currMood == 0)
                setAttachmentsForOverdrive();
            else
                setAttachmentsForDelay();

            setGUIfor3Sliders(currMood);
        }
        else
        {
            if (currMood == 1)
                setAttachmentsForReverb();
            else
                setAttachmentsForChorus();

            setGUIfor4Sliders(currMood);
        }

        toggleButtonTheme.setMood(currMood);

        sliderTheme.setMood(currMood);

        juce::Colour labelColour;
        switch (static_cast<int>(currMood))
        {
            case 0: labelColour = juce::Colour(OVERDRIVE_COLOUR); break;
            case 1: labelColour = juce::Colour(REVERB_COLOUR); break;
            case 2: labelColour = juce::Colour(CHORUS_COLOUR); break;
            case 3: labelColour = juce::Colour(DELAY_COLOUR); break;
        }
        fxLabel->setColour (juce::Label::textColourId, labelColour);
        //[/UserSliderCode_moodSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PluginEditor::setAttachmentsForChorus()
{
    attachmentsReset();

    rateAttachment.reset(new SliderAttachment(valueTreeState, Parameters::NAME_RATE, *slider1));
    intensityAttachment.reset(new SliderAttachment(valueTreeState, Parameters::NAME_INTENSITY, *slider2));
    amountAttachment.reset(new SliderAttachment(valueTreeState, Parameters::NAME_AMOUNT, *slider3));
    stereoWidthAttachment.reset(new SliderAttachment(valueTreeState, Parameters::NAME_STEREO_WIDTH, *slider4));

    statusAttachment.reset(new ButtonAttachment(valueTreeState, Parameters::CHORUS_ACTIVE, *effectStatus));
    effectStatus->setButtonText(juce::String("Chorus"));
}

void PluginEditor::setAttachmentsForDelay()
{
    attachmentsReset();

    delayTimeAttachment.reset(new SliderAttachment(valueTreeState, Parameters::NAME_DELAY_TIME, *slider1));
    feedbackAttachment.reset(new SliderAttachment(valueTreeState, Parameters::NAME_FEEDBACK, *slider2));
    delayDryWetAttachment.reset(new SliderAttachment(valueTreeState, Parameters::NAME_DELAY_DRY_WET, *slider3));

    statusAttachment.reset(new ButtonAttachment(valueTreeState, Parameters::DELAY_ACTIVE, *effectStatus));
    effectStatus->setButtonText(juce::String("Delay"));
}

void PluginEditor::setAttachmentsForReverb()
{
    attachmentsReset();

    roomSizeAttachment.reset(new SliderAttachment(valueTreeState, Parameters::NAME_ROOM_SIZE, *slider1));
    dampingAttachment.reset(new SliderAttachment(valueTreeState, Parameters::NAME_DAMPING, *slider2));
    widthAttachment.reset(new SliderAttachment(valueTreeState, Parameters::NAME_REVERB_WIDTH, *slider3));
    reverbDryWetAttachment.reset(new SliderAttachment(valueTreeState, Parameters::NAME_REVERB_DRY_WET, *slider4));

    statusAttachment.reset(new ButtonAttachment(valueTreeState, Parameters::REVERB_ACTIVE, *effectStatus));
    effectStatus->setButtonText(juce::String("Reverb"));
}

void PluginEditor::setAttachmentsForOverdrive()
{
    attachmentsReset();

    gainAttachment.reset(new SliderAttachment(valueTreeState, Parameters::NAME_GAIN, *slider1));
    toneAttachment.reset(new SliderAttachment(valueTreeState, Parameters::NAME_TONE, *slider2));
    outputLvlAttachment.reset(new SliderAttachment(valueTreeState, Parameters::NAME_OUTPUT_LEVEL, *slider3));

    statusAttachment.reset(new ButtonAttachment(valueTreeState, Parameters::OVERDRIVE_ACTIVE, *effectStatus));
    effectStatus->setButtonText(juce::String("Overdrive"));
}

void PluginEditor::attachmentsReset()
{
    statusAttachment.reset();

    // Chorus
    rateAttachment.reset();
    intensityAttachment.reset();
    amountAttachment.reset();
    stereoWidthAttachment.reset();

    // Delay
    delayTimeAttachment.reset();
    feedbackAttachment.reset();
    delayDryWetAttachment.reset();

    // Reverb
    roomSizeAttachment.reset();
    dampingAttachment.reset();
    widthAttachment.reset();
    reverbDryWetAttachment.reset();

    // Overdrive
    gainAttachment.reset();
    toneAttachment.reset();
    outputLvlAttachment.reset();
}

void PluginEditor::setGUIfor3Sliders (int mood)
{
    switch (mood)
    {
        case 0: // angry
        {
            sl1Label->setText(juce::String("GAIN (dB)"), NotificationType::dontSendNotification);
            sl2Label->setText(juce::String("TONE (dB)"), NotificationType::dontSendNotification);
            sl3Label->setText(juce::String("OUTPUT LEVEL (dB)"), NotificationType::dontSendNotification);

            effectLabel->setText(juce::String("OVERDRIVE"), NotificationType::dontSendNotification);
            effectLabel->setColour(juce::Label::textColourId, juce::Colour(OVERDRIVE_COLOUR));
        } break;

        case 3: // sad
        {
            sl1Label->setText(juce::String("DELAY TIME (s)"), NotificationType::dontSendNotification);
            sl2Label->setText(juce::String("FEEDBACK"), NotificationType::dontSendNotification);
            sl3Label->setText(juce::String("DRY/WET"), NotificationType::dontSendNotification);

            effectLabel->setText(juce::String("DELAY"), NotificationType::dontSendNotification);
            effectLabel->setColour(juce::Label::textColourId, juce::Colour(DELAY_COLOUR));
        } break;
    }

    if (!slider4->isVisible()) // If there are already 3 sliders doesn't do anything
        return;

    // Slider 4 and its label NOT visibile
    slider4->setVisible(false);
    sl4Label->setVisible(false);

    // Moving slider 3 and label 3 to the right
    slider3->setBounds(slider3->getX() + OFFSET, slider3->getY(), slider3->getWidth(), slider3->getHeight());
    sl3Label->setBounds(sl3Label->getX() + OFFSET, sl3Label->getY(), sl3Label->getWidth(), sl3Label->getHeight());
}

void PluginEditor::setGUIfor4Sliders (int mood)
{
    switch (mood)
    {
        case 2: // happy
        {
            sl1Label->setText(juce::String("RATE (Hz)"), NotificationType::dontSendNotification);
            sl2Label->setText(juce::String("INTENSITY"), NotificationType::dontSendNotification);
            sl3Label->setText(juce::String("AMOUNT"), NotificationType::dontSendNotification);
            sl4Label->setText(juce::String("STEREO WIDTH"), NotificationType::dontSendNotification);

            effectLabel->setText(juce::String("CHORUS"), NotificationType::dontSendNotification);
            effectLabel->setColour(juce::Label::textColourId, juce::Colour(CHORUS_COLOUR));
        } break;

        case 1: // chill
        {
            sl1Label->setText(juce::String("ROOM SIZE"), NotificationType::dontSendNotification);
            sl2Label->setText(juce::String("DAMPING"), NotificationType::dontSendNotification);
            sl3Label->setText(juce::String("STEREO WIDTH"), NotificationType::dontSendNotification);
            sl4Label->setText(juce::String("DRY/WET"), NotificationType::dontSendNotification);

            effectLabel->setText(juce::String("REVERB"), NotificationType::dontSendNotification);
            effectLabel->setColour(juce::Label::textColourId, juce::Colour(REVERB_COLOUR));
        } break;
    }

    if (slider4->isVisible()) // If there are already 4 sliders doesn't do anything
        return;

    // Moving slider 3 and label 3 to the left
    slider3->setBounds(slider3->getX() - OFFSET, slider3->getY(), slider3->getWidth(), slider3->getHeight());
    sl3Label->setBounds(sl3Label->getX() - OFFSET, sl3Label->getY(), sl3Label->getWidth(), sl3Label->getHeight());

    // Slider 4 and its label visible
    slider4->setVisible(true);
    sl4Label->setVisible(true);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PluginEditor" componentName=""
                 parentClasses="public juce::AudioProcessorEditor" constructorParams="MoodFXAudioProcessor&amp; p, AudioProcessorValueTreeState&amp; vts"
                 variableInitialisers="AudioProcessorEditor (&amp;p), processor (p), valueTreeState (vts)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="710" initialHeight="450">
  <BACKGROUND backgroundColour="ffebebeb">
    <ROUNDRECT pos="10 10 690 430" cornerSize="10.0" fill="solid: 10525252"
               hasStroke="1" stroke="1.5, mitered, butt" strokeColour="solid: ff3e3e3e"/>
    <RECT pos="340 50 1 350" fill="solid: 3e3e3e" hasStroke="1" stroke="1, mitered, butt"
          strokeColour="solid: ff3e3e3e"/>
    <TEXT pos="35 343 280 30" fill="solid: ff3e3e3e" hasStroke="0" text="Let your mood choose the sound."
          fontname="Rajdhani" fontsize="16.0" kerning="0.0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="68 262 64 30" fill="solid: ff3e3e3e" hasStroke="0" text="ANGRY"
          fontname="Rajdhani" fontsize="15.0" kerning="0.0" bold="0" italic="0"
          justification="34"/>
    <TEXT pos="220 262 64 30" fill="solid: ff3e3e3e" hasStroke="0" text="SAD"
          fontname="Rajdhani" fontsize="15.0" kerning="0.0" bold="0" italic="0"
          justification="33"/>
    <TEXT pos="55 141 64 30" fill="solid: ff3e3e3e" hasStroke="0" text="CHILL"
          fontname="Rajdhani" fontsize="15.0" kerning="0.0" bold="0" italic="0"
          justification="34"/>
    <TEXT pos="231 141 64 30" fill="solid: ff3e3e3e" hasStroke="0" text="HAPPY"
          fontname="Rajdhani" fontsize="15.0" kerning="0.0" bold="0" italic="0"
          justification="33"/>
  </BACKGROUND>
  <SLIDER name="Slider 1" id="393e15d7d8617259" memberName="slider1" virtualName="CustomSlider"
          explicitFocusOrder="0" pos="388 88 110 110" textboxtext="ff3e3e3e"
          textboxoutline="408e989b" min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.0" needsCallback="0"/>
  <SLIDER name="Slider 2" id="c4d62368d05346fb" memberName="slider2" virtualName="CustomSlider"
          explicitFocusOrder="0" pos="543 88 110 110" textboxtext="ff3e3e3e"
          textboxoutline="408e989b" min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.0" needsCallback="0"/>
  <SLIDER name="Slider 4" id="e85e9b2c64135784" memberName="slider4" virtualName="CustomSlider"
          explicitFocusOrder="0" pos="543 256 110 110" textboxtext="ff3e3e3e"
          textboxoutline="408e989b" min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.0" needsCallback="0"/>
  <TOGGLEBUTTON name="Active" id="1395a75b84c5f878" memberName="effectStatus"
                virtualName="CustomToggleButton" explicitFocusOrder="0" pos="506 394 37 26"
                buttonText="" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <SLIDER name="Slider 3" id="963dbbc9a65978fd" memberName="slider3" virtualName="CustomSlider"
          explicitFocusOrder="0" pos="388 256 110 110" textboxtext="ff3e3e3e"
          textboxoutline="408e989b" min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.0" needsCallback="0"/>
  <LABEL name="Slider 1 label" id="4cdb35715d281c0e" memberName="sl1Label"
         virtualName="" explicitFocusOrder="0" pos="383 61 120 24" textCol="ff3e3e3e"
         edTextCol="ff000000" edBkgCol="0" labelText="slider 1 label"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Rajdhani" fontsize="20.0" kerning="0.0" bold="0" italic="0"
         justification="36"/>
  <LABEL name="Slider 2 label" id="b99f33b2c29fa687" memberName="sl2Label"
         virtualName="" explicitFocusOrder="0" pos="538 61 120 24" textCol="ff3e3e3e"
         edTextCol="ff000000" edBkgCol="0" labelText="slider 2 label"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Rajdhani" fontsize="20.0" kerning="0.0" bold="0" italic="0"
         justification="36"/>
  <LABEL name="Slider 3 label" id="dcbd50bed6b596a5" memberName="sl3Label"
         virtualName="" explicitFocusOrder="0" pos="383 229 120 24" textCol="ff3e3e3e"
         edTextCol="ff000000" edBkgCol="0" labelText="slider 3 label"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Rajdhani" fontsize="20.0" kerning="0.0" bold="0" italic="0"
         justification="36"/>
  <LABEL name="Slider 4 label" id="51a624266e7a6543" memberName="sl4Label"
         virtualName="" explicitFocusOrder="0" pos="538 229 120 24" textCol="ff3e3e3e"
         edTextCol="ff000000" edBkgCol="0" labelText="slider 4 label"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Rajdhani" fontsize="20.0" kerning="0.0" bold="0" italic="0"
         justification="36"/>
  <SLIDER name="Mood Slider" id="ff7a132ebde3136" memberName="moodSlider"
          virtualName="CustomSlider" explicitFocusOrder="0" pos="110 145 130 130"
          textboxtext="ff000000" textboxoutline="8e989b" min="0.0" max="10.0"
          int="0.0" style="RotaryVerticalDrag" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <LABEL name="Mood selector label" id="90fa9187722f4a1b" memberName="moodSelectorLabel"
         virtualName="" explicitFocusOrder="0" pos="115 305 120 24" textCol="ff3e3e3e"
         edTextCol="ff000000" edBkgCol="0" labelText="MOOD SELECTOR&#10;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Rajdhani" fontsize="20.0" kerning="0.0" bold="0" italic="0"
         justification="36" typefaceStyle="Medium"/>
  <LABEL name="Effect label" id="ae457220eaa95b48" memberName="effectLabel"
         virtualName="" explicitFocusOrder="0" pos="377 395 114 24" textCol="ff3e3e3e"
         edTextCol="ff000000" edBkgCol="0" labelText="slider 3 label"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Rajdhani" fontsize="20.0" kerning="0.0" bold="0" italic="0"
         justification="34" typefaceStyle="Medium"/>
  <LABEL name="ON/OFF label" id="a7ef5b27d89f622c" memberName="onOffLabel"
         virtualName="" explicitFocusOrder="0" pos="554 395 56 24" textCol="ff3e3e3e"
         edTextCol="ff000000" edBkgCol="0" labelText="ON/OFF" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Rajdhani"
         fontsize="20.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="Mood" id="9f0612371807b6f8" memberName="nameLabel" virtualName=""
         explicitFocusOrder="0" pos="88 49 78 39" textCol="ff3e3e3e" edTextCol="ff000000"
         edBkgCol="0" labelText="Mood" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Rajdhani" fontsize="40.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="Name" id="3ffbb937577ffed6" memberName="fxLabel" virtualName=""
         explicitFocusOrder="0" pos="140 49 78 39" textCol="ff3e3e3e"
         edTextCol="ff000000" edBkgCol="0" labelText="FX&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Rajdhani"
         fontsize="40.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="by BIME" id="7d8d77b38ffb4a23" memberName="byLabel" virtualName=""
         explicitFocusOrder="0" pos="192 54 78 39" textCol="ff3e3e3e"
         edTextCol="ff000000" edBkgCol="0" labelText="by BIME" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Rajdhani"
         fontsize="20.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="Effect setup" id="bdb8aeaa872cdb4c" memberName="effectSetupLabel"
         virtualName="" explicitFocusOrder="0" pos="471 10 100 39" textCol="ff3e3e3e"
         edTextCol="ff000000" edBkgCol="0" labelText="EFFECT SETUP&#10;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Rajdhani" fontsize="20.0" kerning="0.0" bold="0" italic="0"
         justification="36" typefaceStyle="Medium"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

