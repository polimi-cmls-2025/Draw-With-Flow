s.reboot;
Server.killAll;

~moodChords = (
	angry: [ [55, 59, 62], [48, 52, 55], [55, 59, 62], [53, 57, 60] ],
	chill: [ [48, 52, 55], [53, 57, 60], [48, 52, 55], [55, 59, 62] ],
	happy: [ [48, 52, 55], [55, 59, 62], [53, 57, 60], [53, 57, 60] ],
	sad: [ [57, 60, 64], [48, 52, 55], [53, 57, 60], [53, 57, 60] ],
);

////////// Plugin parameter mapping //////////

~moodToParam = (
	angry: "ANGRY",
	chill: "CHILL",
	happy: "HAPPY",
	sad:   "SAD",
);

~currentMood = \angry;
~progression = ~moodChords[~currentMood];

// VST plugin synthdef
SynthDef(\pluginVST, {
    arg inBus, outBus=0;
    var inSig, proc;

    inSig = In.ar(inBus, 2);

    proc = VSTPlugin.ar(inSig, 2, id: \plugin);

	Out.ar(outBus, proc);
}).add;


s.waitForBoot {
	// VST Plugin defs and init
	VSTPlugin.search;

	~vstBus = Bus.audio(s, 2);

	~vstSynth = Synth(\pluginVST, [\inBus, ~vstBus, \outBus, 0]);

	~vstCtrl = VSTPluginController(~vstSynth, id:\plugin);
	~vstCtrl.open("MoodFX.vst3", editor:true, verbose:true);

	~currentMood = \angry;
    ~normalBpm = 60;
    ~doubleBpm = ~normalBpm * 2;
    ~currentBpm = ~normalBpm;

    // Function to update mood and bpm
    ~setMood = { |mood|
        if (mood == \angry or: { mood == \happy }) {
            if (~currentBpm != ~doubleBpm) {
                ~currentBpm = ~doubleBpm;
            };
        } {
            if (~currentBpm != ~normalBpm) {
                ~currentBpm = ~normalBpm;
            };
        };
        ~currentMood = mood;
		~progression = ~moodChords[~currentMood];
		~vstCtrl.set(18, ~moodToParam[~currentMood]);
	};

	// Init with the starting mood
	~setMood.(~currentMood);

    // Mood OSC listener
    OSCdef(\moodListener, { |msg|
        var newMood = msg[1].asSymbol;
        ~setMood.(newMood);
    }, '/mood');

	// Rate OSC listener
	OSCdef(\rateListener, { |msg|
		var newValue = msg[1];
        ~vstCtrl.set(0, newValue);
	}, '/setRate');

	// Stereo Width OSC listener
	OSCdef(\stWidthListener, { |msg|
		var newValue = msg[1];
        ~vstCtrl.set(1, newValue);
	}, '/setStereoWidth');

	// Intensity OSC listener
	OSCdef(\intensityListener, { |msg|
		var newValue = msg[1];
        ~vstCtrl.set(2, newValue);
	}, '/setIntensity');

	// Amount OSC listener
	OSCdef(\amountListener, { |msg|
		var newValue = msg[1];
        ~vstCtrl.set(3, newValue);
	}, '/setAmount');

	// Chorus ON/OFF OSC listener
	OSCdef(\chorusStatusListener, { |msg|
		var newValue = msg[1];
        ~vstCtrl.set(4, newValue);
	}, '/setChorusStatus');

	// Delay time OSC listener
	OSCdef(\delayTimeListener, { |msg|
		var newValue = msg[1];
        ~vstCtrl.set(5, newValue);
	}, '/setDelayTime');

	// Delay dry/wet OSC listener
	OSCdef(\delayDwListener, { |msg|
		var newValue = msg[1];
        ~vstCtrl.set(6, newValue);
	}, '/setDelayDw');

	// Feedback OSC listener
	OSCdef(\feedbackListener, { |msg|
		var newValue = msg[1];
        ~vstCtrl.set(7, newValue);
	}, '/setFeedback');

	// Delay ON/OFF OSC listener
	OSCdef(\delayStatusListener, { |msg|
		var newValue = msg[1];
        ~vstCtrl.set(8, newValue);
	}, '/setDelayStatus');

	// Room Size OSC listener
	OSCdef(\roomSizeListener, { |msg|
		var newValue = msg[1];
        ~vstCtrl.set(9, newValue);
	}, '/setRoomSize');

	// Damping OSC listener
	OSCdef(\dampingListener, { |msg|
		var newValue = msg[1];
        ~vstCtrl.set(10, newValue);
	}, '/setDamping');

	// Width OSC listener
	OSCdef(\widthListener, { |msg|
		var newValue = msg[1];
        ~vstCtrl.set(11, newValue);
	}, '/setWidth');

	// Reverb dry/wet OSC listener
	OSCdef(\reverbDwListener, { |msg|
		var newValue = msg[1];
        ~vstCtrl.set(12, newValue);
	}, '/setReverbDw');

	// Reverb ON/OFF OSC listener
	OSCdef(\reverbStatusListener, { |msg|
		var newValue = msg[1];
        ~vstCtrl.set(13, newValue);
	}, '/setReverbStatus');

	// Gain OSC listener
	OSCdef(\gainListener, { |msg|
		var newValue = msg[1];
        ~vstCtrl.set(14, newValue);
	}, '/setGain');

	// Tone OSC listener
	OSCdef(\toneListener, { |msg|
		var newValue = msg[1];
        ~vstCtrl.set(15, newValue);
	}, '/setTone');

	// Output Level OSC listener
	OSCdef(\outputLvlListener, { |msg|
		var newValue = msg[1];
        ~vstCtrl.set(16, newValue);
	}, '/setOutputLevel');

	// OVerdrive ON/OFF OSC listener
	OSCdef(\overdriveStatusListener, { |msg|
		var newValue = msg[1];
        ~vstCtrl.set(17, newValue);
	}, '/setOverdriveStatus');

	// Bpm listener
	OSCdef(\bmpListener, { |msg|
		var newBpm = msg[1];
		 if (~currentMood == \angry or: { ~currentMood == \happy }) {
			~currentBpm = newBpm;
        } {
		~currentBpm = newBpm*0.5;
		}
	}, '/setBpm');

	////////// 1. SynthDef //////////


	// ------- Beat synths definitions

	// Kick synth definition
	SynthDef(\kick, {
		arg bus = 0;
		var env = EnvGen.kr(Env.perc(0.001, 0.3), doneAction: 2);
		var pitchEnv = EnvGen.kr(Env([80, 55], [0.05]));
		var osc = SinOsc.ar(pitchEnv) * env * 0.9;
		var clickEnv = EnvGen.kr(Env.perc(0.001, 0.01));
		var click = BPF.ar(WhiteNoise.ar, 2500, 0.95) * clickEnv * 0.2;
		var outSig = (osc + click) ! 2;

		Out.ar(bus, outSig);
	}).add;

	// Snare synth definition
	SynthDef(\snare, {
		arg bus = 0;
		var env = EnvGen.kr(Env.perc(0.005, 0.2), doneAction: 2);
		var noise = BPF.ar(WhiteNoise.ar, 500, 0.65) * env * 0.8;
		var body = SinOsc.ar(200, 0, 0.35) * env;
		var outSig = noise + body;
		noise = BPF.ar(WhiteNoise.ar, 1200, 0.65) * env * 0.8;
		outSig = noise + body;

		Out.ar(bus, outSig!2);
	}).add;

	// Hi-hat synth definition
	SynthDef(\hihat, {
		arg bus = 0;
		var env = EnvGen.kr(Env.perc(0.001, 0.05), doneAction: 2);
		var outSig = HPF.ar(WhiteNoise.ar, 10000, 0.6) * env * 0.5;

		Out.ar(bus, outSig!2);
	}).add;


	// ------- Musical synths definitions


	// Angry guitar synth definition (angry mood)
	 SynthDef(\angryGtr, {
        arg bus=0, freq=110, amp=0.5, dur=1, cutoff=2500;
        var env, sig, pan;

        env = EnvGen.kr(Env.perc(0.005, dur, amp, -4), doneAction:2);
        sig = Saw.ar([freq*0.99, freq*1.01]).sum * env;
        sig = LPF.ar(sig, cutoff);

        pan = Pan2.ar(sig, 0);

        Out.ar(bus, pan);
    }).add;

	// Pad synth definition (chill mood)
	SynthDef(\pad, {
		arg bus = 0, freqs = #[440, 550, 660], amp = 0.5, dur = 1.5, cutoff = 1000;
		var env, sig, detune, pan;

		env = EnvGen.kr(Env.linen(0.5, dur, 1.5), doneAction: 2);

		sig = Mix.fill(freqs.size, { |i|
			var o = Saw.ar(freqs[i], amp/freqs.size);
			LPF.ar(o, cutoff)
		});
		detune = DelayC.ar(sig, 0.03, SinOsc.kr(0.1).range(0.015, 0.045));
		sig = (sig + detune) * env;

		pan = Pan2.ar(sig, 0);

		Out.ar(bus, pan);
	}).add;

	// Sad synth definition (sad mood)
	SynthDef(\sadSynth, {
		arg bus = 0, freqs = #[440, 550, 660], amp = 0.5, dur = 3, maxdelay = 0.1, decay = 2, cutoff = 4000;
		var env, sig, plucks, shimmer, pan;

		env = EnvGen.kr(Env.perc(0.005, dur, amp, -6), doneAction: 2);

		plucks = freqs.collect { |freq|
			var p = Pluck.ar(
				WhiteNoise.ar(0.4),
				maxdelaytime: maxdelay,
				delaytime: 1/freq,
				decaytime: decay,
				coef: 0.5
			);
			LPF.ar(p, cutoff)
		};

		shimmer = Mix(freqs.collect { |freq|
			SinOsc.ar(freq * 2.01, 0, 0.1)
		});

		sig = (Mix.new(plucks) + shimmer) * env * amp;

		pan = Pan2.ar(sig, 0);

		Out.ar(bus, pan);
	}).add;


	// Happy guitar synth definition (happy mood)
	SynthDef(\happyGtr, {
		arg bus = 0, freq = 440, amp = 0.5, dur = 1, cutoff = 2000;
		var env, osc, noise, distorted, sig, pan;

		env = EnvGen.kr(Env.perc(0.01, dur, amp, -4), doneAction: 2);

		osc = Pulse.ar(freq, 0.5);
		noise = WhiteNoise.ar(0.2);
		distorted = osc + (noise * 0.4);

		sig = LPF.ar(distorted, cutoff) * env;

		pan = Pan2.ar(sig, 0);

		Out.ar(bus, pan);
	}).add;

	////////// Routine: music generation //////////

	~chordIndex = 0;

	~musicSeq = Routine({

		var beatCount = 0;
		var subBeatCount = 0;

		loop {

			~eighthDur = (60 / ~currentBpm) / 2;

			// Every 4 beats (8 eighths), it plays a new chord
			if (subBeatCount % 8 == 0) {
				var chord = ~progression.wrapAt(~chordIndex);
				var freqs = chord.collect(_.midicps);

				if (~currentMood == \angry) {
					chord.do { |note|
						Synth(\angryGtr, [
							\bus,  ~vstBus,
							\freq, note.midicps
						]);
					};
				};


				if (~currentMood == \happy) {
					chord.do { |note|
						Synth(\happyGtr, [
							\bus,  ~vstBus,
							\freq, note.midicps
						]);
					};
				};

				if (~currentMood == \chill) {
					Synth(\pad, [\bus, ~vstBus, \freqs, freqs]);
				};

				if (~currentMood == \sad ) {
					Synth(\sadSynth, [\bus, ~vstBus, \freqs, freqs]);
				};

				~chordIndex = ~chordIndex + 1;
			};


			// If the mood is not sad, also the drum-machine goes into the VST plugin.
			if (~currentMood != \sad) {
				// Kick
				if (subBeatCount % 8 == 0 or: { subBeatCount % 8 == 5 }) {
					Synth(\kick, [\bus, ~vstBus]);
				};

				// Snare
				if (subBeatCount % 8 == 2 or: { subBeatCount % 8 == 6 }) {
					Synth(\snare, [\bus, ~vstBus]);
				};
				// Hi-hat
				Synth(\hihat, [\bus, ~vstBus]);
			} {
				// sad -> stereo bus
				if (subBeatCount % 8 == 0 or: { subBeatCount % 8 == 5 }) {
					Synth(\kick);
				};
				if (subBeatCount % 8 == 2 or: { subBeatCount % 8 == 6 }) {
					Synth(\snare);
				};
				Synth(\hihat);
			};

			subBeatCount = subBeatCount + 1;
			if (subBeatCount % 2 == 0) { beatCount = beatCount + 1 }; // every 2 eighth -> 1 beat

			~eighthDur.wait;
		}
	}).play();
};

~musicSeq.stop;

~vstCtrl.editor;

~vstCtrl.gui;
