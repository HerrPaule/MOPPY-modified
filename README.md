MOPPY-modified
==============

based on SammyIAm's Moppy code. Use Floppy with usbmidi (Teensy), Pure Data or Max/MSP.
SammyIAm source: https://github.com/SammyIAm/Moppy


Teensy (2.0++) usbmidi
==============
Use usbmidi to control the floppydrives. I tested it with Teensy 2.0++, 16 Floppydrives & 16 MIDI Channels.
Maybe you can use the HIDUINO FW to run your Arduino Board with MIDI over USB. Change the "usbmidi" commands to "midi" (watch MIDI Library). I haven't tested it right now. 


Max/MSP & Pure Data
==============
Use the orginal Arduino Sketch with Max/MSP or Pure Data. No further modification are necessary. Max/MSP or Pure Data will send the same byte commands as SammyIAm's MOPPYDESK. You don't have to install the JAVA RXTX drivers.
Check the PDF for details of the send byte command.

The Pure Data version works with Raspberry Pi & PD-extended. 
