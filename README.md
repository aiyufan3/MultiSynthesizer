#  MultiSynthesizer


##  Selection title: "Closer-Chainsmoker Remix"



##  Basic Description:  
Leveraging musical sheets of the song "Closer" by Chainsmoker online, with a developed Python solution that translates the notes of "Closer" into structured score files. Utilizing the advanced capabilities of the Synthine platform under development, we've integrated multiple distinct synthesizer instruments into the final 'Project1' score file. Upon opening this Score file, it undergoes real-time processing to synthesize the culminating musical piece.


https://github.com/aiyufan3/MultiSynthesizer/assets/55717488/7fd27ad4-bf24-4f58-8726-a861c0874f10


###  Synthesizer used in the project:

**Additive Synthesizer:**

https://github.com/aiyufan3/MultiSynthesizer/assets/55717488/2081017e-752f-4e4c-bfbf-7d5e9478a670

An additive synthesizer generates sound by adding together multiple sine wave harmonics. Each harmonic has its frequency and amplitude, allowing for the creation of complex tones. This method is based on the principle that any sound can be broken down into a collection of sine waves.

*10 - Sinusoid playback on demand from the sequencer*

*20 - Definition of all harmonics*

*30 - Envelope generation*

*35 - Polyphony*

*40 - Sound cross-fading*

*50 - Vibrato OR glissando*

**Organ Synthesizer:**

https://github.com/aiyufan3/MultiSynthesizer/assets/55717488/ffa934f0-5c18-4d9e-8fcb-9b8a423adcbe

The organ synthesizer emulates the sound of traditional pipe organs. It uses drawbars to control the volume of multiple harmonic partials, allowing for a wide range of tonal possibilities. Additional effects such as Leslie speakers and vibrato can be applied to enhance the sound.

*10 - Tonewheels*

*20 - Drawbars*

*30 - Envelope generation*

*40 - Vibrato*

*50 - Leslie speaker*
**Subtractive Synthesizer:**

https://github.com/aiyufan3/MultiSynthesizer/assets/55717488/36e005a5-9109-4b6a-b762-569ec78e879f

Subtractive synthesis involves sculpting sound by removing certain frequencies from a harmonically rich waveform. This is typically achieved using filters. By adjusting parameters like resonance and cutoff frequency, a variety of timbres can be produced.

*10 - Waveform playback from tables*

*20 - Varying pitch playback from tables*

*30 - Envelope generation*

*35 - Polyphony*

*40 - Reson implementation and the Moog sound*

*50 - Filter envelopes*

###  Five-Effect-Component:


https://github.com/aiyufan3/MultiSynthesizer/assets/55717488/448fe1f4-b15a-479e-8e6f-217f9e24b00e


**Reverberation:**

Reverberation, or reverb, simulates the natural reflections of sound in a physical space. It adds depth and spaciousness to the sound, making it feel as if it's being played in a room or hall.

**Chorus:**

The chorus effect duplicates the input signal and slightly detunes and delays the duplicate. This creates a richer, thicker sound, simulating multiple instruments or voices playing in unison.

**Noise Gate:**

Noise gating is a dynamic processor that mutes the signal when its level falls below a set threshold. It's useful for eliminating unwanted background noise or hum when the main signal is not present.

**Flange:**

Flanging is a time-based effect that mixes the input signal with a delayed version of itself. This produces a sweeping comb filter effect, creating a characteristic 'whooshing' or 'jet plane' sound.

**Compression:**

Compression is a dynamic effect that reduces the dynamic range of a signal. It makes quiet sounds louder and loud sounds quieter, ensuring a more consistent volume level and enhancing the sustain of musical instruments.

*10 - Component passes audio*

*20 - 1 Effect*

*30 - 3 Effects*

*40 - Controllable effects send*

*50 - 4 Effects*

##  Format of Score Files:

**Basic Tone Synthesis:**
	
 	instrument instrument="ToneInstrument"
  
    	note measure="" beat="" duration="" note=""

measure: Specifies the measure in which the note begins. This helps in positioning the note within the musical piece.

beat: Indicates the specific beat within the measure where the note starts. This provides a finer granularity in positioning the note.

duration: Defines the duration for which the note will play, measured in seconds. A value of 0 indicates that the note will play for its full duration.

note: Indicates the pitch of the note that will be played, such as "C4" or "A#5".

**Additive Synthesis:**

	instrument instrument="AdditiveInstrument"
 
		note measure="" beat="" duration="" note="" harmonics="" vibrato="" vibratoRate="" crossfade=""
  
measure: Specifies the measure in which the note begins. This helps in positioning the note within the musical piece.

beat: Indicates the specific beat within the measure where the note starts. This provides a finer granularity in positioning the note.

duration: Defines the duration for which the note will play, measured in seconds. A value of 0 indicates that the note will play for its full duration.

note: Indicates the pitch of the note that will be played, such as "C4" or "A#5".

harmonics: Represents the harmonic intervals or intervals that will be utilized in the sound. In additive synthesis, sound is generated by adding together individual sine waves with different frequencies (harmonics). This parameter can specify which harmonics are included and their relative amplitudes.

vibrato: Specifies the intensity of the vibrato effect. Vibrato is a periodic variation in pitch, which can add warmth and expressiveness to a sound.

vibratoRate: Defines how quickly the "shaking" or oscillation of the vibrato effect occurs. A higher rate will result in faster oscillations, while a lower rate will produce slower oscillations.

crossfade: Indicates whether crossfading is applied to the sound. Crossfading is a technique where the end of one sound gradually fades out while the beginning of another sound fades in. The value can be "1" for crossfade or "0" for no crossfade.

**Organ Synthesis:**

 	 instrument instrument="Organ"
  
    	note measure="" beat="" duration="" note="" amplitude="" drawbar="" attack="" decay="" release="" leslieRadius="" leslieAttackTime="" leslieFreq="" vibratoFreq="" vibratoFlag=""

measure: Specifies the measure in which the note begins. This helps in positioning the note within the musical piece.

beat: Indicates the specific beat within the measure where the note starts. This provides a finer granularity in positioning the note

duration: Defines the duration for which the note will play, measured in seconds. A value of 0 indicates that the note will play for its full duration.

note: Indicates the pitch of the note that will be played, such as "C4" or "A#5".

amplitude: Determines the loudness or volume of the note.

drawbar: Represents the drawbar settings for the organ, which can shape the tonal quality of the note. It's a series of numbers that dictate the volume of various harmonic components of the sound.

attack: Specifies the time it takes for the note to reach its maximum amplitude after it starts playing.

decay: Defines the time it takes for the note to decrease from its maximum amplitude to its sustained level.

release: Indicates the time it takes for the note to decrease from its sustained level to silence after it stops playing.

leslieRadius: Determines the radius of the Leslie speaker effect, which can add a unique rotating sound characteristic to the organ.

leslieAttackTime: Specifies the time it takes for the Leslie effect to reach its maximum intensity.

leslieFreq: Sets the frequency of the Leslie speaker rotation.

vibratoFreq: Defines the frequency of the vibrato effect, determining how quickly the pitch oscillates.

vibratoFlag: A binary value where 1 indicates that a vibrato effect should be applied, and 0 means no vibrato.

**Subtractive Synthesis:**
 instrument instrument="SubtractiveInstrument"
 
    note measure="" beat="" duration="" note="" wavetype="" resonFreq="" bandwidth="" sweep=""
    
measure: Specifies the measure in which the note begins. This helps in positioning the note within the musical piece.

beat: Indicates the specific beat within the measure where the note starts. This provides a finer granularity in positioning the note.

duration: Defines the duration for which the note will play, measured in seconds. A value of 0 indicates that the note will play for its full duration.

note: Indicates the pitch of the note that will be played, such as "C4" or "A#5".

wavetype: Represents the type of waveform that will be used as the sound source. Common waveforms in subtractive synthesis include "sine", "sawtooth", "square", and "triangle".

resonFreq: Specifies the resonant frequency of the filter. This is the frequency at which the filter will boost or cut the sound the most. Adjusting the resonant frequency can emphasize or de-emphasize certain harmonics in the sound.

bandwidth: Defines the width of the frequency band that the filter will affect. A narrower bandwidth will affect a smaller range of frequencies, while a wider bandwidth will affect a larger range.

sweep: Indicates if there's a filter sweep applied to the sound. A filter sweep is a change in the filter's cutoff frequency over time, which can create dynamic and evolving sounds. The value can specify the direction and speed of the sweep.  

**Effects:**
-  instrument instrument="Compress"
-  instrument instrument="Reverb"
-  instrument instrument="Flange"
-  instrument instrument="Chorus"
-  instrument instrument="NoiseGate"
  
    		note measure="" delay="" wet="" dry="" threshold=""

measure: Specifies the measure in which the effect is applied. This helps in positioning the effect within the musical piece.

delay: Represents the amount of time (usually in milliseconds) before the echoed sound is heard. This parameter is commonly associated with delay or echo effects, where the original sound is played back after a short period of time, creating an echo.

wet: Refers to the amount or level of the processed signal in the final mix. In effects processing, the "wet" signal is the one that has been affected by the effect, such as reverb or chorus.

dry: Refers to the amount or level of the original, unprocessed signal in the final mix. In a mix, the "dry" signal is the original sound without any effects applied.

threshold: Specifies the level at which the effect is activated or deactivated. This parameter is commonly associated with noise gates or compressors. For a noise gate, any signal below the threshold will be silenced, while signals above the threshold will pass through.

###  Extra feature:  
Menu Handler of Effects - Leveraging the principles of synthesizer generation, effects are seamlessly integrated into the menu interface, enabling users to modify sound dynamics instantaneously. 

**Note: The actual score files are all in the score folder, and the generated music samples are in the music folder, scoregen is the folder to generate samples of score files**

