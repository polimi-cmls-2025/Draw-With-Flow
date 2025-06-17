#pragma once
#include <JuceHeader.h>

namespace Parameters
{

// Core constants
constexpr int NUM_CHANNELS = 2;
constexpr float MAX_DELAY_TIME = 5.0f;

// ----------------------------------------------------------------------------------

// CHORUS
constexpr float CHORUS_DELAY_TIME               = 0.020f; // Chorus delay time: 20 ms
constexpr float SMOOTHING_TIME                  = 0.1f;

// ------------------------------

// RATE parameter
static const String NAME_RATE                   = "RT";
constexpr float RATE_FLOOR                      = 0.1f;
constexpr float RATE_CEILING                    = 20.0f;
constexpr float DEFAULT_RATE                    = 0.1f;
constexpr float RATE_SKEW_FACTOR                = 0.4f;

// ------------------------------

// INTENSITY parameter
// The intensity value appears in the user interface between 0 and 100%.
// The value is then mapped to the range [INTENSITY_FLOOR; INTENSITY_CEILING]
static const String NAME_INTENSITY              = "IN";
constexpr float INTENSITY_FLOOR                 = 0.0f;
constexpr float INTENSITY_CEILING               = 1000.0f * CHORUS_DELAY_TIME * 0.25f;
constexpr float DEFAULT_INTENSITY               = 0.0f;
constexpr float INTENSITY_SKEW_FACTOR           = 0.42f;

// ------------------------------

// STEREO WIDTH parameter
// The stereo width value appears in the user interface between 0 and 100%.
// The value is then mapped to the range [STEREO_WIDTH_FLOOR; STEREO_WIDTH_CEILING]
static const String NAME_STEREO_WIDTH           = "SW";
constexpr float STEREO_WIDTH_FLOOR              = 0.0f;
constexpr float STEREO_WIDTH_CEILING            = 0.5f;
constexpr float DEFAULT_STEREO_WIDTH            = 0.0f;

// ------------------------------

// AMOUNT parameter (Dry/Wet)
// The amount value appears in the user interface between 0 and 100%.
// The value is then mapped to the range [AMOUNT_FLOOR; AMOUNT_CEILING]
static const String NAME_AMOUNT                 = "AM";
constexpr float AMOUNT_FLOOR                    = 0.0f;
constexpr float AMOUNT_CEILING                  = 1.0f;
constexpr float DEFAULT_DW_RATIO                = 0.5f;

// ------------------------------

// ACTIVE parameter
static const String CHORUS_ACTIVE               = "CA";

// ----------------------------------------------------------------------------------

// DELAY

// DELAY TIME parameter
// The delay time ranges between 0.05 and 5 seconds
static const String NAME_DELAY_TIME             = "DT";
constexpr float DELAY_TIME_FLOOR                = 0.05f;
constexpr float DEFAULT_DELAY_TIME              = 1.0f;

// ------------------------------

// FEEDBACK parameter
// The feedback value appears in the user interface between 0 and 100%.
// The value is then mapped to the range [0.0f, 0.5f]
static const String NAME_FEEDBACK               = "FB";
constexpr float FEEDBACK_FLOOR                  = 0.0f;
constexpr float FEEDBACK_CEILING                = 0.5f;
constexpr float DEFAULT_FEEDBACK                = 0.0f;

// ------------------------------

// DRY/WET parameter
// The dry/wet value appears in the user interface between 0 and 100%.
// The value is then mapped to the range [AMOUNT_FLOOR; AMOUNT_CEILING]
static const String NAME_DELAY_DRY_WET          = "D_DW";

// ------------------------------

// ACTIVE parameter
static const String DELAY_ACTIVE                = "DA";

// ----------------------------------------------------------------------------------

// REVERB

// ROOM SIZE parameter
// The room size value appears in the user interface between 0 and 100%.
// The value is then mapped to the range [0.0f, 1.0f]
static const String NAME_ROOM_SIZE              = "RS";
constexpr float ROOM_SIZE_FLOOR                 = 0.0f;
constexpr float ROOM_SIZE_CEILING               = 1.0f;
constexpr float DEFAULT_ROOM_SIZE               = 0.5f;

// ------------------------------

// DAMPING parameter
// The damping value appears in the user interface between 0 and 100%.
// The value is then mapped to the range [0.0f, 1.0f]
static const String NAME_DAMPING                = "DM";
constexpr float DAMPING_FLOOR                   = 0.0f;
constexpr float DAMPING_CEILING                 = 1.0f;
constexpr float DEFAULT_DAMPING                 = 0.5f;

// ------------------------------

// WIDTH parameter
// The width value appears in the user interface between 0 and 100%.
// The value is then mapped to the range [0.0f, 1.0f]
static const String NAME_REVERB_WIDTH                  = "WD";
constexpr float REVERB_WIDTH_FLOOR                     = 0.0f;
constexpr float REVERB_WIDTH_CEILING                   = 1.0f;
constexpr float REVERB_DEFAULT_WIDTH                   = 1.0f;

// ------------------------------

// DRY/WET parameter
// The dry/wet value appears in the user interface between 0 and 100%.
// The value is then mapped to the range [AMOUNT_FLOOR; AMOUNT_CEILING]
static const String NAME_REVERB_DRY_WET         = "R_DW";

// ------------------------------

// ACTIVE parameter
static const String REVERB_ACTIVE               = "RA";

// ----------------------------------------------------------------------------------

// OVERDRIVE

// GAIN parameter
// The gain value appears in the user interface between 0 dB and 20 dB.
static const String NAME_GAIN                   = "GN";
constexpr float GAIN_FLOOR                      = 0.0f;
constexpr float GAIN_CEILING                    = 20.0f;
constexpr float DEFAULT_GAIN                    = 0.0f;

// ------------------------------

// TONE parameter
// The tone value appears in the user interface between -6 dB and +6 dB.
static const String NAME_TONE                   = "TN";
constexpr float TONE_FLOOR                      = - 12.0f;
constexpr float TONE_CEILING                    = + 12.0f;
constexpr float DEFAULT_TONE                    = 0.0f;

constexpr float TONE_FREQUENCY                  = 2400.0f;
constexpr float TONE_Q_FACTOR                   = 1.10f;

// ------------------------------

// OUTPUT LEVEL parameter
// The output level value appears in the user interface between -12 dB and +6 dB.
static const String NAME_OUTPUT_LEVEL           = "OL";
constexpr float OUTPUT_LEVEL_FLOOR              = - 12.0f;
constexpr float OUTPUT_LEVEL_CEILING            = + 6.0f;
constexpr float DEFAULT_OUTPUT_LEVEL            = 0.0f;
constexpr float OUTPUT_LEVEL_SKEW_FACTOR        = 0.585f;

// ------------------------------

// ACTIVE parameter
static const String OVERDRIVE_ACTIVE            = "OA";

// ----------------------------------------------------------------------------------

// Useful constants
constexpr float LFO_RAMP_LENGTH                 = 0.01f;
constexpr float MA_RAMP_LENGTH                  = 0.02f;
constexpr float PAR_RAMP_LENGTH                 = 0.2f;
constexpr float NORM_RANGE_STEP                 = 0.01f;
constexpr float PERC_FLOOR                      = 0.0f;
constexpr float PERC_CEILING                    = 100.0f;
constexpr float DEFAULT_PERC                    = 0.0f;
constexpr float DEFAULT_SKEW_FACTOR             = 1.0f;

constexpr bool DEFAULT_ACTIVE                   = false;

// ----------------------------------------------------------------------------------

// MOOD paramter
static const String NAME_MOOD                   = "MD";

static AudioProcessorValueTreeState::ParameterLayout createParameterLayout ()
{
    std::vector<std::unique_ptr<RangedAudioParameter>> parameters;
    
    
    // CHORUS parameters
    parameters.push_back(std::make_unique<AudioParameterFloat>(ParameterID(NAME_RATE, 1), "Rate (Hz)", NormalisableRange<float>(RATE_FLOOR, RATE_CEILING, NORM_RANGE_STEP, RATE_SKEW_FACTOR), DEFAULT_RATE));
    parameters.push_back(std::make_unique<AudioParameterFloat>(ParameterID(NAME_STEREO_WIDTH, 1), "Stereo Width", PERC_FLOOR, PERC_CEILING, DEFAULT_PERC));
    parameters.push_back(std::make_unique<AudioParameterFloat>(ParameterID(NAME_INTENSITY, 1), "Intensity", NormalisableRange<float>(PERC_FLOOR, PERC_CEILING, NORM_RANGE_STEP, INTENSITY_SKEW_FACTOR), DEFAULT_PERC));
    parameters.push_back(std::make_unique<AudioParameterFloat>(ParameterID(NAME_AMOUNT, 1), "Amount", PERC_FLOOR, PERC_CEILING, DEFAULT_PERC));
    parameters.push_back(std::make_unique<AudioParameterBool>(ParameterID(CHORUS_ACTIVE, 1), "Chorus ON/OFF", DEFAULT_ACTIVE));
    
    
    // DELAY parameters
    parameters.push_back(std::make_unique<AudioParameterFloat>(ParameterID(NAME_DELAY_TIME, 1), "Delay Time (s)", NormalisableRange<float>(DELAY_TIME_FLOOR, MAX_DELAY_TIME, NORM_RANGE_STEP, 0.4), DEFAULT_DELAY_TIME));
    parameters.push_back(std::make_unique<AudioParameterFloat>(ParameterID(NAME_DELAY_DRY_WET, 1), "Delay Dry/Wet", PERC_FLOOR, PERC_CEILING, DEFAULT_PERC));
    parameters.push_back(std::make_unique<AudioParameterFloat>(ParameterID(NAME_FEEDBACK, 1), "Feedback", PERC_FLOOR, PERC_CEILING, DEFAULT_PERC));
    parameters.push_back(std::make_unique<AudioParameterBool>(DELAY_ACTIVE, "Delay ON/OFF", DEFAULT_ACTIVE));
    
    
    // REVERB parameters
    parameters.push_back(std::make_unique<AudioParameterFloat>(ParameterID(NAME_ROOM_SIZE, 1), "Room size", PERC_FLOOR, PERC_CEILING, DEFAULT_PERC));
    parameters.push_back(std::make_unique<AudioParameterFloat>(ParameterID(NAME_DAMPING, 1), "Damping", PERC_FLOOR, PERC_CEILING, DEFAULT_PERC));
    parameters.push_back(std::make_unique<AudioParameterFloat>(ParameterID(NAME_REVERB_WIDTH, 1), "Width", PERC_FLOOR, PERC_CEILING, DEFAULT_PERC));
    parameters.push_back(std::make_unique<AudioParameterFloat>(ParameterID(NAME_REVERB_DRY_WET, 1), "Reverb Dry/Wet", PERC_FLOOR, PERC_CEILING, DEFAULT_PERC));
    parameters.push_back(std::make_unique<AudioParameterBool>(REVERB_ACTIVE, "Reverb ON/OFF", DEFAULT_ACTIVE));
    
    
    // OVERDRIVE parameters
    parameters.push_back(std::make_unique<AudioParameterFloat>(ParameterID(NAME_GAIN, 1), "Gain (dB)", NormalisableRange<float>(GAIN_FLOOR, GAIN_CEILING, NORM_RANGE_STEP, DEFAULT_SKEW_FACTOR), DEFAULT_GAIN));
    parameters.push_back(std::make_unique<AudioParameterFloat>(ParameterID(NAME_TONE, 1), "Tone (dB)", NormalisableRange<float>(TONE_FLOOR, TONE_CEILING, NORM_RANGE_STEP, DEFAULT_SKEW_FACTOR), DEFAULT_TONE));
    parameters.push_back(std::make_unique<AudioParameterFloat>(ParameterID(NAME_OUTPUT_LEVEL, 1), "Output level (dB)", NormalisableRange<float>(OUTPUT_LEVEL_FLOOR, OUTPUT_LEVEL_CEILING, NORM_RANGE_STEP, OUTPUT_LEVEL_SKEW_FACTOR), DEFAULT_OUTPUT_LEVEL));
    parameters.push_back(std::make_unique<AudioParameterBool>(OVERDRIVE_ACTIVE, "Overdrive ON/OFF", DEFAULT_ACTIVE));
    
    // MOOD parameter
    parameters.push_back(std::make_unique<AudioParameterChoice>(ParameterID(NAME_MOOD, 1), "Mood", juce::StringArray{"ANGRY", "CHILL", "HAPPY", "SAD"}, 0));
    
    return {parameters.begin(), parameters.end()};
}

static void addListenerToAllParameters (AudioProcessorValueTreeState& valueTreeState, AudioProcessorValueTreeState::Listener* listener)
{
    std:: unique_ptr<XmlElement> xml(valueTreeState.copyState().createXml());
    
    for (auto element : xml->getChildWithTagNameIterator("PARAM"))
    {
        const String& id = element->getStringAttribute("id");
        valueTreeState.addParameterListener(id, listener);
    }
}
}

namespace Moods
{
// MOODS parameters

inline static constexpr bool EFFECT_STATUS = true;

// Angry (overdrive)
struct preset_angry
{
    inline static constexpr float GAIN = 10.0f; 
    inline static constexpr float TONE = 1.5f;
    inline static constexpr float OUTPUT_LEVEL = -9.5f;
};

// ------------------------------

// Chill (reverb)
struct preset_chill
{
    inline static constexpr float ROOM_SIZE = 67.0f;
    inline static constexpr float DAMPING = 35.0f;
    inline static constexpr float WIDTH = 100.0f;
    inline static constexpr float DW_RATIO = 32.0f;
};

// ------------------------------

// Happy (chorus)
struct preset_happy
{
    inline static constexpr float RATE = 3.5f;
    inline static constexpr float INTENSITY = 30.0f;
    inline static constexpr float STEREO_WIDTH = 100.0f;
    inline static constexpr float AMOUNT = 45.0f;
};

// ------------------------------

// Sad (delay)
struct preset_sad
{
    inline static constexpr float DELAY_TIME = 1.5f;
    inline static constexpr float FEEDBACK = 8.5f;
    inline static constexpr float DW_RATIO = 35.0f;
};
}
