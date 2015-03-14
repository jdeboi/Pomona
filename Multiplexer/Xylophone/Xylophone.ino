/*
  Arduinio Xylophone
  March 2015
  Pomona College

  CREDIT
  Mark Demers Copyright 2009 http://spikenzielabs.com/SpikenzieLabs/DrumKitKit.html
  Georg Mill's YAAMIDrum www.georgmill.de/

  This exercise is designed to introduce multiplexers. Check out the Arduino
  reference on the 4051 http://www.arduino.cc/playground/Learning/4051

  INSTALL
  AC Tone Library http://playground.arduino.cc/Code/ToneAC
*/

#include <toneAC.h>

int speakerPin = 3;
unsigned char PadNote[8] = { 262, 196, 196, 220, 196, 0, 247, 262 };	 //array containing frequencies

unsigned char status;
int PadCutOff[8] = {80, 110, 110, 110, 80, 110, 110, 110};	 //array containing "threshold" values;
int MaxPlayTime[8] = {90, 90, 90, 90, 90, 90, 90, 90};		 //time each note remains on after being hit

boolean activePad[8] = {0, 0, 0, 0, 0, 0, 0, 0};            // array of flags of pad currently playing
int PinPlayTime[8] = {0, 0, 0, 0, 0, 0, 0, 0};              // counter since pad started to play
boolean VelocityFlag = true;				    // set this variable to true if you'd like the volume
int analogPin = A0;                                         //to correspond to force of hit
int hitForce = 0;
int pad = 0;

int r0 = 0;      //value of select pin at the 4051 (s0)
int r1 = 0;      //value of select pin at the 4051 (s1)
int r2 = 0;      //value of select pin at the 4051 (s2)
int count = 0;   //which y pin we are selecting

int multiplex[8];

//*******************************************************************************************************************
// Setup
//*******************************************************************************************************************

void setup() {
  pinMode(2, OUTPUT);    // s0
  pinMode(3, OUTPUT);    // s1
  pinMode(4, OUTPUT);    // s2
  Serial.begin(9600);
}

//*******************************************************************************************************************
// Main Program
//*******************************************************************************************************************

void loop () {
  readSensors();
  checkSensors();
}

void readSensors () {
  ///////////////////
  // MULTIPLEXER
  ///////////////////
  for (count = 0; count <= 7; count++) {
    r2 = bitRead(count, 0);    	      
    r1 = bitRead(count, 1);
    r0 = bitRead(count, 2);
    digitalWrite(2, r0);		
    digitalWrite(3, r1);
    digitalWrite(4, r2);
    multiplex[count] = analogRead(analogPin);

    /*Serial.print(count);		          //use these functions to test/print out count (effectively piezo number)
    Serial.print(" ");                            //and voltage (0-1023) of each piezo
    Serial.println(multiplex[count]);
    */
  }
}

void checkSensors() {		
  for (int pin = 0; pin <= 7; pin++) {
    hitForce = multiplex[pin];			//variable hitForce equals the analogRead() (0-1023) of the piezo
    pad = pin;
    if ((hitForce > PadCutOff[pin])) {		
      if ((activePad[pad] == false)) {	 
        playKey(PadNote[pad], hitForce);   
        PinPlayTime[pad] = 0;			
        activePad[pad] = true;			
      }
      else {					
        PinPlayTime[pad] = PinPlayTime[pad] + 1;
      }
    }
  }
}


////////////////////////////////////////////////////////////////
// MAKE SOUND
////////////////////////////////////////////////////////////////
void playKey(int freq, int velocity) {
  if (VelocityFlag == true) {
    velocity = velocity / 100;		
  }					
  else {
    velocity = 10;  
  }
  noToneAC();
  int duration = map(velocity, 0, 1023, 0, 500);
  toneAC(freq, velocity, duration, true);
}
