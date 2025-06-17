#define OVERDRIVE_COLOUR                    0xffae3731
#define REVERB_COLOUR                       0xffc548b0
#define CHORUS_COLOUR                       0xff7ac548
#define DELAY_COLOUR                        0xff49acc8

#define THEME_COLOUR                        0xfffca311
#define KNOB_COLOUR                         0xff3e3e3e
#define POINTER_COLOUR                      0xffd4d4d6

#define GRAY_COLOUR                         0xff8e8e8e

constexpr float KNOB_DIMENSION_REDUCER      = 15.0f;
constexpr float POINTER_THICKNESS           = 3.0f;
constexpr float TICKS_THICKNESS             = 3.5f;
constexpr float KNOB_TO_TICK_RATIO          = 0.78f;
constexpr float BORDER_WIDTH                = 2.25f;

#pragma once

class CustomSlider : public juce::Slider
{
    public:
    CustomSlider(const juce::String& sliderName) : juce::Slider(sliderName) {}
    
    void mouseEnter(const juce::MouseEvent&) override
    {
        setMouseCursor(juce::MouseCursor::PointingHandCursor);
    }
    
    void mouseExit(const juce::MouseEvent&) override
    {
        setMouseCursor(juce::MouseCursor::NormalCursor);
    }
};

class CustomToggleButton : public juce::ToggleButton
{
    public:
    CustomToggleButton(const juce::String& buttonName) : juce::ToggleButton(buttonName) {}
    
    void mouseEnter(const juce::MouseEvent&) override
    {
        setMouseCursor(juce::MouseCursor::PointingHandCursor);
    }
    
    void mouseExit(const juce::MouseEvent&) override
    {
        setMouseCursor(juce::MouseCursor::NormalCursor);
    }
};

// Look and feel for Toggle button
class ToggleButtonTheme : public juce::LookAndFeel_V4
{
public:
    ToggleButtonTheme (int mood = 0)
    {
        currentMood = mood;
        setMoodColour();
    }
    
    void setMood (int newMood)
    {
        currentMood = newMood;
        setMoodColour();
    }
    
    void setMoodColour ()
    {
        switch (currentMood)
        {
            case 0: moodColour = juce::Colour(OVERDRIVE_COLOUR); break;
            case 1: moodColour = juce::Colour(REVERB_COLOUR); break;
            case 2: moodColour = juce::Colour(CHORUS_COLOUR); break;
            case 3: moodColour = juce::Colour(DELAY_COLOUR); break;
        }
    }
    
    void drawToggleButton(juce::Graphics& g, juce::ToggleButton& button,
                          bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override
    {
        const auto bounds = button.getLocalBounds().toFloat().reduced(1.0f);
        const bool isOn = button.getToggleState();

        const float diameter = std::min(bounds.getWidth(), bounds.getHeight());
        const auto centre = bounds.getCentre();
        const auto circleBounds = juce::Rectangle<float>(diameter, diameter).withCentre(centre);

        auto baseColor = juce::Colour(KNOB_COLOUR).brighter(0.9);
        auto outlineColor = juce::Colour(KNOB_COLOUR);

        g.setColour(isOn ? moodColour : baseColor);
        g.fillEllipse(circleBounds);

        g.setColour(outlineColor);
        g.drawEllipse(circleBounds, 2.0f);
    }

    
private:
    int currentMood = 0;
    juce::Colour moodColour;
    
};

class SliderTheme : public juce::LookAndFeel_V4
{
public:
    SliderTheme (int mood = 0, MoodFXAudioProcessor* proc = nullptr)
    {
        currentMood = mood;
        setMoodColour();
        processor = proc;
    }
    
    void setMood (int newMood)
    {
        currentMood = newMood;
        setMoodColour();
    }
    
    void attachProcessor (MoodFXAudioProcessor* proc)
    {
        processor = proc;
    }
    
    void setMoodColour ()
    {
        switch (currentMood)
        {
            case 0: moodColour = juce::Colour(OVERDRIVE_COLOUR); break;
            case 1: moodColour = juce::Colour(REVERB_COLOUR); break;
            case 2: moodColour = juce::Colour(CHORUS_COLOUR); break;
            case 3: moodColour = juce::Colour(DELAY_COLOUR); break;
                
            case 4: moodColour = juce::Colour(GRAY_COLOUR); break; // Mood selector
                
            default: moodColour = juce::Colour(GRAY_COLOUR); break; // For sliders when the effect is not active
        }
    }

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                          float sliderPosProportional, float rotaryStartAngle,
                          float rotaryEndAngle, juce::Slider& slider) override
    {
        const float radius = juce::jmin(width, height) / 2.0f - KNOB_DIMENSION_REDUCER;
        const float centreX = x + width * 0.5f;
        const float centreY = y + height * 0.5f;
        const float rx = centreX - radius;
        const float ry = centreY - radius;
        const float angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);

        // Knob
        g.setColour(juce::Colour(KNOB_COLOUR));
        g.fillEllipse(rx, ry, radius * 2.0f, radius * 2.0f);

        // Outline of the knob
        g.setColour(juce::Colours::black);
        g.drawEllipse(rx, ry, radius * 2.0f, radius * 2.0f, 4.0f);

        // Arc around
        if (currentMood != 4)
        {
            const float arcThickness = 3.5f;
            const float arcRadius = radius + arcThickness * 0.5f + 5.0f;
            
            juce::Path entireArc;
            
            entireArc.addArc(centreX - arcRadius, centreY - arcRadius,
                            arcRadius * 2.0f, arcRadius * 2.0f,
                            rotaryStartAngle, rotaryEndAngle, true);
            g.setColour(juce::Colour(GRAY_COLOUR).brighter(0.7));
            g.strokePath(entireArc, juce::PathStrokeType(arcThickness));
            
            juce::Path valueArc;
            valueArc.addArc(centreX - arcRadius, centreY - arcRadius,
                            arcRadius * 2.0f, arcRadius * 2.0f,
                            rotaryStartAngle, angle, true);
            
            g.setColour(moodColour);
            g.strokePath(valueArc, juce::PathStrokeType(arcThickness));
            
            
        }

        // Pointer
        float pointerRadius = 2.5f;
        if (currentMood == 4)
            pointerRadius = 3.5f;
        const float pointerDistance = radius * 0.75f;

        juce::Path pointer;
        pointer.addEllipse(-pointerRadius, -pointerDistance - pointerRadius,
                           pointerRadius * 2.0f, pointerRadius * 2.0f);

        juce::AffineTransform transform = juce::AffineTransform::rotation(angle).translated(centreX, centreY);

        // To make the dot on the slider (only for the mood selector slider) the same colour as the selected mood in the processor.
        if (currentMood == 4)
        {
            juce::Colour processorMoodColour;
            switch (processor->getCurrentMood())
            {
                case 0: processorMoodColour = juce::Colour(OVERDRIVE_COLOUR); break;
                case 1: processorMoodColour = juce::Colour(REVERB_COLOUR); break;
                case 2: processorMoodColour = juce::Colour(CHORUS_COLOUR); break;
                case 3: processorMoodColour = juce::Colour(DELAY_COLOUR); break;
            }
            g.setColour(processorMoodColour);
        }

        else
            g.setColour(juce::Colour(POINTER_COLOUR));
        g.fillPath(pointer, transform);
        
        if (currentMood == 4)
        {
            Path originalTickShape, t;
            originalTickShape.addEllipse(-TICKS_THICKNESS * 0.5f, radius / - KNOB_TO_TICK_RATIO, TICKS_THICKNESS, TICKS_THICKNESS);
            g.setColour(Colours::black);
            
            for (int i = 0; i < 4; ++ i)
            {
                t = originalTickShape;
                auto normValue = pow((float)i / (4 - 1), (float)slider.getSkewFactor());
                float angle = jmap(normValue, rotaryStartAngle, rotaryEndAngle);
                t.applyTransform(AffineTransform::rotation(angle).translated(centreX, centreY));
                g.fillPath(t);
            }
        }
        
    }
    
    juce::Font getLabelFont(juce::Label& label) override
    {
        return juce::Font ("Rajdhani", 18.0f, juce::Font::plain).withTypefaceStyle ("Regular");
    }

private:
    int currentMood;
    juce::Colour moodColour;
    
    MoodFXAudioProcessor* processor;
};


