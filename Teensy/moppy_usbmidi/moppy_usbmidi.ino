/*
this sketch is based on SammyIAm Moppy Sketch.
I only make some additional modification to use the the original Moopy sketch with Teensy usbmidi functions.

the original sketch & SammyIAm Source can be found at: https://github.com/SammyIAm/Moppy
*/


#include <TimerOne.h>

boolean firstRun = true; // Used for one-run-only stuffs;
int freqNote = 0;
int floppyCh = 0;
//First pin being used for floppies, and the last pin.  Used for looping over all pins.
const byte FIRST_PIN = 2;
const byte PIN_MAX = 33;
#define RESOLUTION 40 //Microsecond resolution for notes


/*NOTE: Many of the arrays below contain unused indexes.  This is 
 to prevent the Arduino from having to convert a pin input to an alternate
 array index and save as many cycles as possible.  In other words information 
 for pin 2 will be stored in index 2, and information for pin 4 will be 
 stored in index 4.*/


/*An array of maximum track positions for each step-control pin.  Even pins
 are used for control, so only even numbers need a value here.  3.5" Floppies have
 80 tracks, 5.25" have 50.  These should be doubled, because each tick is now
 half a position (use 158 and 98).
 */
byte MAX_POSITION[] = {
  0,0,158,0,158,0,158,0,158,0,158,0,158,0,158,0,158,0,158,0,158,0,158,0,158,0,158,0,158,0,158,0,158,0};

//Array to track the current position of each floppy head.  (Only even indexes (i.e. 2,4,6...) are used)
byte currentPosition[] = {
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

/*Array to keep track of state of each pin.  Even indexes track the control-pins for toggle purposes.  Odd indexes
 track direction-pins.  LOW = forward, HIGH=reverse
 */
int currentState[] = {
  0,0,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW
};

//Current period assigned to each pin.  0 = off.  Each period is of the length specified by the RESOLUTION
//variable above.  i.e. A period of 10 is (RESOLUTION x 10) microseconds long.
unsigned int currentPeriod[] = {
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

//Current tick
unsigned int currentTick[] = {
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 
};



//Setup pins (Even-odd pairs for step control and direction
void setup(){
  //pinMode(13, OUTPUT);// Pin 13 has an LED connected on most Arduino boards
  pinMode(2, OUTPUT); // Step control 1
  pinMode(3, OUTPUT); // Direction 1
  pinMode(4, OUTPUT); // Step control 2
  pinMode(5, OUTPUT); // Direction 2
  pinMode(6, OUTPUT); // Step control 3
  pinMode(7, OUTPUT); // Direction 3
  pinMode(8, OUTPUT); // Step control 4
  pinMode(9, OUTPUT); // Direction 4
  pinMode(10, OUTPUT); // Step control 5
  pinMode(11, OUTPUT); // Direction 5
  pinMode(12, OUTPUT); // Step control 6
  pinMode(13, OUTPUT); // Direction 6
  pinMode(14, OUTPUT); // Step control 7
  pinMode(15, OUTPUT); // Direction 7
  pinMode(16, OUTPUT); // Step control 8
  pinMode(17, OUTPUT); // Direction 8

  pinMode(18, OUTPUT); // Step control 9
  pinMode(19, OUTPUT); // Direction 9
  pinMode(20, OUTPUT); // Step control 10
  pinMode(21, OUTPUT); // Direction 10
  pinMode(22, OUTPUT); // Step control 11
  pinMode(23, OUTPUT); // Direction 11
  pinMode(24, OUTPUT); // Step control 12
  pinMode(25, OUTPUT); // Direction 12
  pinMode(26, OUTPUT); // Step control 13
  pinMode(27, OUTPUT); // Direction 13
  pinMode(28, OUTPUT); // Step control 14
  pinMode(29, OUTPUT); // Direction 14
  pinMode(30, OUTPUT); // Step control 15
  pinMode(31, OUTPUT); // Direction 15
  pinMode(32, OUTPUT); // Step control 16
  pinMode(33, OUTPUT); // Direction 16

  Timer1.initialize(RESOLUTION); // Set up a timer at the defined resolution
  Timer1.attachInterrupt(tick); // Attach the tick function

  Serial.begin(9600);

  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn);
}
void OnNoteOff(byte channel, byte note, byte velocity) { 
  floppyCh = channel*2;
  currentPeriod[floppyCh] = 0;

}

void OnNoteOn(byte channel, byte note, byte velocity) {
  switch (note){
  case 24: 
    freqNote = 381;
    break;
  case 25:
    freqNote = 359;
    break;  
  case 26:
    freqNote = 339;
    break;
  case 27:
    freqNote = 320;
    break;
  case 28:
    freqNote = 302;
    break;
  case 29:
    freqNote = 285;
    break;
  case 30:
    freqNote = 269;
    break;
  case 31:
    freqNote = 255;
    break;
  case 32:
    freqNote = 240;
    break;
  case 33:
    freqNote = 227;
    break;
  case 34:
    freqNote = 214;
    break;
  case 35:
    freqNote = 202;
    break;
  case 36: 
    freqNote = 191;
    break;
  case 37:
    freqNote = 180;
    break;  
  case 38:
    freqNote = 170;
    break;
  case 39:
    freqNote = 160;
    break;
  case 40:
    freqNote = 151;
    break;
  case 41:
    freqNote = 143;
    break;
  case 42:
    freqNote = 135;
    break;
  case 43:
    freqNote = 127;
    break;
  case 44:
    freqNote = 120;
    break;
  case 45:
    freqNote = 113;
    break;
  case 46:
    freqNote = 107;
    break;
  case 47:
    freqNote = 101;
    break;
  case 48:
    freqNote = 95;
    break;
  case 49:
    freqNote = 90;
    break;
  case 50:
    freqNote = 85;
    break;
  case 51:
    freqNote = 80;
    break;
  case 52:
    freqNote = 75;
    break;
  case 53:
    freqNote = 71;
    break;
  case 54:
    freqNote = 67;
    break;
  case 55:
    freqNote = 63;
    break;
  case 56:
    freqNote = 60;
    break;
  case 57:
    freqNote = 56;
    break;
  case 58:
    freqNote = 53;
    break;
  case 59:
    freqNote = 50;
    break;     
  case 60: 
    freqNote = 47;
    break;
  case 61:
    freqNote = 45;
    break;  
  case 62:
    freqNote = 42;
    break;
  case 63:
    freqNote = 40;
    break;
  case 64:
    freqNote = 37;
    break;
  case 65:
    freqNote = 35;
    break;
  case 66:
    freqNote = 33;
    break;
  case 67:
    freqNote = 31;
    break;
  case 68:
    freqNote = 30;
    break;
  case 69:
    freqNote = 28;
    break;
  case 70:
    freqNote = 26;
    break;
  case 71:
    freqNote = 25;
    break;
  }
  floppyCh = channel * 2;
  currentPeriod[floppyCh] = freqNote;
}

void loop(){
  usbMIDI.read(); // USB MIDI receive

  //The first loop, reset all the drives, and wait 2 seconds...
  if (firstRun)
  {
    firstRun = false;
    resetAll();
    delay(2000);
  }
}


/*
Called by the timer inturrupt at the specified resolution.
 */
void tick()
{
  /* 
   If there is a period set for control pin 2, count the number of
   ticks that pass, and toggle the pin if the current period is reached.
   */
  if (currentPeriod[2]>0){
    currentTick[2]++;
    if (currentTick[2] >= currentPeriod[2]){
      togglePin(2,3);
      currentTick[2]=0;
    }
  }
  if (currentPeriod[4]>0){
    currentTick[4]++;
    if (currentTick[4] >= currentPeriod[4]){
      togglePin(4,5);
      currentTick[4]=0;
    }
  }
  if (currentPeriod[6]>0){
    currentTick[6]++;
    if (currentTick[6] >= currentPeriod[6]){
      togglePin(6,7);
      currentTick[6]=0;
    }
  }
  if (currentPeriod[8]>0){
    currentTick[8]++;
    if (currentTick[8] >= currentPeriod[8]){
      togglePin(8,9);
      currentTick[8]=0;
    }
  }
  if (currentPeriod[10]>0){
    currentTick[10]++;
    if (currentTick[10] >= currentPeriod[10]){
      togglePin(10,11);
      currentTick[10]=0;
    }
  }
  if (currentPeriod[12]>0){
    currentTick[12]++;
    if (currentTick[12] >= currentPeriod[12]){
      togglePin(12,13);
      currentTick[12]=0;
    }
  }
  if (currentPeriod[14]>0){
    currentTick[14]++;
    if (currentTick[14] >= currentPeriod[14]){
      togglePin(14,15); 
      currentTick[14]=0;
    }
  }
  if (currentPeriod[16]>0){
    currentTick[16]++;
    if (currentTick[16] >= currentPeriod[16]){
      togglePin(16,17);
      currentTick[16]=0;
    }
  }

  if (currentPeriod[18]>0){
    currentTick[18]++;
    if (currentTick[18] >= currentPeriod[18]){
      togglePin(18,19);
      currentTick[18]=0;
    }
  }
  if (currentPeriod[20]>0){
    currentTick[20]++;
    if (currentTick[20] >= currentPeriod[20]){
      togglePin(20,21);
      currentTick[20]=0;
    }
  }
  if (currentPeriod[22]>0){
    currentTick[22]++;
    if (currentTick[22] >= currentPeriod[22]){
      togglePin(22,23);
      currentTick[6]=0;
    }
  }
  if (currentPeriod[24]>0){
    currentTick[24]++;
    if (currentTick[24] >= currentPeriod[24]){
      togglePin(24,25);
      currentTick[24]=0;
    }
  }
  if (currentPeriod[26]>0){
    currentTick[26]++;
    if (currentTick[26] >= currentPeriod[26]){
      togglePin(26,27);
      currentTick[26]=0;
    }
  }
  if (currentPeriod[28]>0){
    currentTick[28]++;
    if (currentTick[28] >= currentPeriod[28]){
      togglePin(28,29);
      currentTick[28]=0;
    }
  }
  if (currentPeriod[30]>0){
    currentTick[30]++;
    if (currentTick[30] >= currentPeriod[30]){
      togglePin(30,31); 
      currentTick[30]=0;
    }
  }
  if (currentPeriod[32]>0){
    currentTick[32]++;
    if (currentTick[32] >= currentPeriod[32]){
      togglePin(32,33);
      currentTick[32]=0;
    }
  }
}

void togglePin(byte pin, byte direction_pin) {

  //Switch directions if end has been reached
  if (currentPosition[pin] >= MAX_POSITION[pin]) {
    currentState[direction_pin] = HIGH;
    digitalWrite(direction_pin,HIGH);
  } 
  else if (currentPosition[pin] <= 0) {
    currentState[direction_pin] = LOW;
    digitalWrite(direction_pin,LOW);
  }

  //Update currentPosition
  if (currentState[direction_pin] == HIGH){
    currentPosition[pin]--;
  } 
  else {
    currentPosition[pin]++;
  }

  //Pulse the control pin
  digitalWrite(pin,currentState[pin]);
  currentState[pin] = ~currentState[pin];
}


//
//// UTILITY FUNCTIONS
//

//Not used now, but good for debugging...
/*void blinkLED(){
  digitalWrite(13, HIGH); // set the LED on
  delay(250);              // wait for a second
  digitalWrite(13, LOW); 
}
*/
//For a given controller pin, runs the read-head all the way back to 0
void reset(byte pin)
{
  digitalWrite(pin+1,HIGH); // Go in reverse
  for (byte s=0;s<MAX_POSITION[pin];s+=2){ //Half max because we're stepping directly (no toggle)
    digitalWrite(pin,HIGH);
    digitalWrite(pin,LOW);
    delay(5);
  }
  currentPosition[pin] = 0; // We're reset.
  digitalWrite(pin+1,LOW);
  currentPosition[pin+1] = 0; // Ready to go forward.
}

//Resets all the pins
void resetAll(){

  // Old one-at-a-time reset
  //for (byte p=FIRST_PIN;p<=PIN_MAX;p+=2){
  //  reset(p);
  //}

  //Stop all notes (don't want to be playing during/after reset)
  for (byte p=FIRST_PIN;p<=PIN_MAX;p+=2){
    currentPeriod[p] = 0; // Stop playing notes
  }

  // New all-at-once reset
  for (byte s=0;s<80;s++){ // For max drive's position
    for (byte p=FIRST_PIN;p<=PIN_MAX;p+=2){
      digitalWrite(p+1,HIGH); // Go in reverse
      digitalWrite(p,HIGH);
      digitalWrite(p,LOW);
    }
    delay(5);
  }

  for (byte p=FIRST_PIN;p<=PIN_MAX;p+=2){
    currentPosition[p] = 0; // We're reset.
    digitalWrite(p+1,LOW);
    currentState[p+1] = 0; // Ready to go forward.
  }

}







