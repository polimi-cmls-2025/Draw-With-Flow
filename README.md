
# BIME  
BIME Project – Computer Music (Languages and Systems)

**Draw With Flow** – Emotion-Responsive Music Generator

# Purpose

**Draw With Flow** is ideal for:

- Interactive sound installations  
- Multimedia live performances  
- Immersive environments and biofeedback setups  
- Creative experiments with generative music  

The script creates a sonic ecosystem where emotion, body, and technology merge into a unique and ever-changing musical flow.

# MUSIC SEQUENCER – SUPERCOLLIDER

The system developed in SuperCollider generates real-time music that adapts to different emotional states and biometric data captured by external sensors. It’s designed to integrate sound, emotion, and movement into a dynamic and interactive musical experience.

The code creates a generative music sequence that changes based on the selected mood or the one received via OSC messages.  
The supported moods include: *angry, happy, chill, and sad*.  
Each emotional state activates:

- A specific set of chords  
- One or more synths with distinct timbral characteristics  
- A variable musical tempo (BPM)  
- A chain of effects controlled by a VST plugin loaded within the script  

# Integration with Physical Sensors

**Draw With Flow** is designed to be used alongside physical devices capable of detecting biometric and motion parameters. Specifically:

- **Heart Rate Sensor**: The BPM (beats per minute) is calculated from the data detected by a heart rate sensor connected to Arduino.  
  This value determines the tempo of the drum machine, making the rhythm of the composition proportional to the user’s heartbeat.

- **Accelerometer Sensor**: Data from an accelerometer is used to modify the synth and effects parameters in real time.  
  This way, the user’s physical movement directly influences the sound, making it more expressive and responsive.

# GUI – PROCESSING

The interactive graphical interface developed with **Processing** allows real-time control of audio effects in **SuperCollider** based on the selected mood.

# Key Features

- **Circular mood selector** with 4 states: `angry`, `chill`, `happy`, `sad`  
- Each mood is linked to a unique set of **audio effect parameters**  
- Parameter control through **interactive knobs** with non-linear mapping  
- Button to toggle the main effect of the selected mood on or off  
- Sends OSC messages to SuperCollider to update audio parameters in real time  

# UI and UX

- Interface split into two sections: mood selection (left), effect configuration (right)  
- Dynamic visualization of colors and parameters based on the current mood  
- Labels and effects update in real time with visual feedback  

# Mood Mapping

| Mood    | Main Effect | Controllable Parameters                           |
|---------|--------------|--------------------------------------------------|
| Happy   | Chorus        | Rate, Intensity, Amount, Stereo Width           |
| Chill   | Reverb        | Room Size, Damping, Width, Reverb Dry/Wet       |
| Angry   | Overdrive     | Gain, Tone, Output Level                        |
| Sad     | Delay         | Delay Time, Feedback, Delay Dry/Wet             |

# OSC Communication

- Processing listening port: `12000`  
- SuperCollider receives on: `127.0.0.1:57120`  
- Parameters are sent via `/set<ParameterName>` messages  
- Current mood sent via `/mood` message  

# JUCE - PLUGIN
**Mood FX** is a multi-effect VST3 plugin designed as the core of the reactive audio processing in the Draw With Flow system. Developed in C++ using the JUCE framework, the plugin receives OSC messages from the Processing interface and adjusts its internal parameters according to the selected emotional state.

- Integrated audio effects: chorus, delay, reverb, and overdrive — each linked to a specific mood.
- Real-time interactive control: each effect exposes 3 or 4 parameters that are continuously modulated based on incoming OSC messages.
- Dynamic parameter mapping: values received via OSC are normalized and remapped using linear or logarithmic scaling, depending on the parameter type.
- Mood selection and effect toggling: handled externally via the Processing GUI, which sends OSC messages to update the active mood and switch effects on/off in real time.

