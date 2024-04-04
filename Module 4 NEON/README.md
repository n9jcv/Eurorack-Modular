## Module 4 - NEON

This is my version of Random Sequencer/Turing machine.  It is all my own custom design.

*   It has a control for Randomness.  You can set between 0(never pick a random note/lock sequence) or 100(always pick new notes).
*   It has a 4 digit 7 segment display.  TM1637.

<table><tbody><tr><td><ul><li>The first digit to the left indicates how many octaves are currently selected</li></ul></td></tr><tr><td><ul><li>The second digit indicates if the range is Shifted up or down. &nbsp;It is really hard to explain this, much better just to try it out or watch my youtube <a href="https://youtu.be/LqoS8a9SPUM?si=VgSc2C2KI4JfAplC">https://youtu.be/LqoS8a9SPUM?si=VgSc2C2KI4JfAplC</a> demonstrating this visual indication.</li></ul></td></tr><tr><td><ul><li>The third and fourth digit are used to display the step currently being played</li></ul></td></tr></tbody></table>

*   It can generate 2, 3, 4, 5, 6, 8, 12, 16, 32 steps.
*   It has an Octave range of 5+ notes.  The range is 61 Notes, based on 1v/oct.  You can control the range and select from 1 to 5 octaves.
*   It has a Shift range control.  Example, you select 5 steps, and 1 Octave.  You can use the shift control to select one octave range in the 1 to 5.  So highest, lowest or any octave in between.
*   There are 11 LEDs.  The yellow LED in the center is a the Gate LED, and this is lit whenever the gate out is generated.  The 10 other LEDs in a circle are just selected/lit each time a new step is played.  Currently this only happens when Gate out is actually patched to another module.

Schematic and code are available and free for everyone to use. The Schematic does NOT include the cd4017. I purchased a small smd board with the 4017 and a 555 and 10 LEDs, like 50 cents from China. I only soldered the 4017 and the LEDs, I did not use the 555. Instead, I use the D3 output to drive pin 3 of the 555 pad on the board. This triggers the 4017 in sync with the gate.

![Alt text](n9jcv/Eurorack-Modular/tree/main/Module%204%20NEON/Neon Module.jpg?raw=true "Title")

