## Module 8 - CHORD MACHINE

This is my version of Hagiwo's RP2040 Chord module.  The original design can be found here;

[http://https://note.com/solder_state/n/n64b91a171218](http://https://note.com/solder_state/n/n64b91a171218)
Thanks to Hagiwo for sharing!!

The design will require a RP2040.  I am running it on a Seeed Studio Xiao RP2040, but it would likely run on any RP2040, just ensure you change pin numbers as necessary.

I made many changes and customizations to the original code and hardware design.  Please feel free to use this anyway you like.  Here is a list of the functionality as it works with my changes today.

- I added a OLED display.  The SSD1306.  Cheap and looks good.
- I added a 6 step sequencer to the functionality.
- I added a 2 stage buffer output, with a Gain control.  TL072 based.
- I added the ability to generate chords based on external CV input or Internal sequencer.
- I added a clock input, so the chords (either cv based or Internal sequencer) will generate in time with a clock.
- I added a Rotary encoder to control all the selections and the OLED.
- The chord machine has a built in quantizer.
- The chord machine has 6 different chord families to choose from (Major -4 and Minor -2).
- The chord machine can output many waveforms (Sawtooth, Sine, Tri, Square, Octave Saw, FM1, FM2, FM3).


Rotary Encoder Control:  Long pres(4 seconds or more) will activate menu mode.  In this mode you can rotate the encoder and it will highlight individual menue items.  Once the Item you want to change is highlighted, then short press (about 1 second or less) and the highlight will disappear.  That chosen item can not be modified by rotating the encoder.

Internal Sequencer:  The notes are labeled N1 thru N6.  Below each Note label, there is a 00 displayed.  You can select and choose a number between 01 and 31.  There are 7 notes in each quantized scale, so you get about 4 1/2 octaves using 5vpp CV, which is how it is configured.  You can also continue/hold a note simply by leaving the subsequent note as 00.  So if N1 is 07 and N2 is 00, It will play 07 for the duration of N1 and N2.  A horizontal line will appear below the currently playing note, in the Source Internal mode.

Source:  You can select CV, and then send a cv note in and the quantizer will quantize the note and play the chord.  You can select Internal, then the chord machine will need a clock input and will step thru N1 to N6 based on the clock.

Wave:  Select the desired waveform here (Sawtooth, Sine, Tri, Square, Octave Saw, FM1, FM2, FM3)

Chord:  Select the chord family here (Major 1, 2, 3, 4, Minor 1, 2)

Chord Machine Module picture:

![myimage-alt-tag](https://github.com/n9jcv/Eurorack-Modular/blob/main/Module%204%20NEON/Neon%20Module.jpg?raw=true)

Schematic Picture:
![myimage-alt-tag](https://https://github.com/n9jcv/Eurorack-Modular/blob/main/Module%208%20CHORD%20MACHINE/CHORD%20SCHEMATIC.jpg?raw=true)
