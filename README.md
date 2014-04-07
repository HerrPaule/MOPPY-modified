MOPPY-modified
==============

based on SammyIAm's Moppy code. Use Floppy with usbmidi (Teensy), Pure Data or Max/MSP.
SammyIAm source: https://github.com/SammyIAm/Moppy

==============

UPDATE 7.4.2014

My MOPPY Frame is nearly ready. I wrote a detailed description, how to setup a Raspberry Pi in headless mode, which runs a webserver and Pure Data. Pure Data and the HTML page are communicating over websocket. The needed files are at:
- Raspberry Pi Folder
- Teensy Folder

The description can be found at: http://irieelectronics.de/edu/floppy-frame

Here is a short vid of my work:
http://youtu.be/oiNMB_hdTfs

==============

Teensy (2.0++) usbmidi
==============
Use usbmidi to control the floppydrives. I tested it with Teensy 2.0++, 16 Floppydrives & 16 MIDI Channels.
Maybe you can use the HIDUINO FW (https://github.com/ddiakopoulos/hiduino) to run your Arduino Board with MIDI over USB. Change the "usbmidi" commands to "midi" (watch MIDI Library). I haven't tested it right now. Most of the sketch is based on SammyIAm's Arduino sketch.

1. Download & install Teensyduino Add-On for Arduino IDE: https://www.pjrc.com/teensy/td_download.html
2. Open Arduino IDE, go to Tools -> Boards and select your Teensy Board and select at "USB Type" MIDI.
3. upload the sketch to your Teensy.
4. Open your MIDI application, select your Teensy MIDI Port & have fun.

Every MIDI Channel (1-16) will be one of your floppydrives (e.g. MIDI Channel 1 = floppy at Pin 2,3 etc.).
If you're using a Teensy with less Pin, you have to edit the sketch. 


Max/MSP & Pure Data
==============
Use the orginal Arduino Sketch with Max/MSP or Pure Data. No further modification are necessary. Max/MSP or Pure Data will send the same byte commands as SammyIAm's MOPPYDESK. You don't have to install the JAVA RXTX drivers.
Check the PDF for details of the send byte command.

The Pure Data version works with Raspberry Pi & PD-extended. 

1. Download SammyIAm's Arduino Sketch https://github.com/SammyIAm/Moppy
2. Open Arduino IDE & upload the sketch to your Arduino Board.
3. Open the Max/MSP or Pure Data file.
4. Select the MIDI In Port.
5. Setup the Arduino serial port:

- At Max/MSP press "print" messagesbox to get the Arduino serial port. The availble ports will be print at Max Window. Edit the [serial] object the with letter of your Arduino port or select the port by a messagebox with "port Yourportletter" and connect it to the [serial] object.
- At Pure Data press "ports" and check PD Window. Edit the Portnumber of the [serial] object or created a messagebox with "open Yourportnumber" and connect it to [serial]
