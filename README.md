# Eurorack-Modular


# My collection of Modular modules


Module 3 - CV GATE SEQUENCER - this is my version of Hagiwo's CV GATE SEQUENCER.  I modified his code and schematic.  I added 2 Gate outputs, 2 Trigger outputs.  I changed the encoder resolution from 4 to 2.  Added a buffer for the Gate and Trigger outputs.

The original code is at;
https://note.com/solder_state/n/n7c2809976698

It seems to me that the original code had a defect, but maybe Hagiwo intended it to function that way.  The original code would output a note via the DAC, EVEN if the step was turned off.  I modifed the code, and now if you disable a step, there is no output from the DAC for that step.  DAC is 0 volts in that case.
