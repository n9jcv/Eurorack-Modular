# Eurorack-Modular



# Module 1 - VOLTZ
This is my own design for a power supply for a small Eurorack.  It runs off of a 18-24V AC/DC Power Adapter.  Mine is an IBM Laptop power supply.  The Adaptor plugs into 120AC and supplys 4 amps of 19v DC.
This 19vdc is the input to my power supply module.  My power supply will generate 5VDC, +12VDC adn -12VDC.  The 5V is regulated by a LM2596 which should be able to supply 2A.  The +12V and -12V are supplied by a TPS5430 module and should be able to supply 2A. Total current will be dependent on the 19VDC supply and heat of the stepdown converter boards, but I don't plan to push the limits of current.  Both modules take the 19VDC input and convert to the proper output voltages.  I used a cheap digital voltage meter to display the actual voltage of the 5V or th +12V line.  There are LEDs showing that 19V, 5V, +12V and -12V are all working.  Each power rail has a separate fuse.  


# Module 2 - WWVB (The most accurate clock in the world CLOCK MULTIPLY DIVIDE)
This is my version of Hagiwo's Clock Multiply Divide.  Original code/design here (Thanks to Hagiwo);  https://note.com/solder_state/n/n8907f2f6e8f5
Mostly I changed the hardware implementation and panel design.  My version does not have a clock in, it just generates it own clock.  The Base Clock is just that, going to 2 outputs.  Then there is a Clock 1 and Clock 2.  Both are separate and can run at the same speed as the Base Clock, or faster or slower.  The range is divided by 16 to multiplied by 8.  This is a total of 6 Clock outputs.



# Module 3 - CV GATE SEQUENCER
This is my version of Hagiwo's CV GATE SEQUENCER.  I modified his code and schematic.  I added 2 Gate outputs, 2 Trigger outputs.  I changed the encoder resolution to match my encoder.  Added a buffer for the Gate and Trigger outputs.

The original code is at;
https://note.com/solder_state/n/n7c2809976698

It seems to me that the original code had a defect, but maybe Hagiwo intended it to function that way.  The original code would output a note via the DAC, EVEN if the step was turned off.  I modifed the code, and now if you disable a step, there is no output from the DAC for that step.  DAC is 0 volts in that case.
