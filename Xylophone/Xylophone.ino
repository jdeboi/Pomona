/*
* Arduinio Xylophone
* March 2015
* Pomona College
*
* CREDIT
* Mark Demers Copyright 2009 http://spikenzielabs.com/SpikenzieLabs/DrumKitKit.html
* Georg Mill's YAAMIDrum www.georgmill.de/
* 
* This exercise is designed to introduce multiplexers. Check out the Arduino
* reference on the 4051 http://www.arduino.cc/playground/Learning/4051
*
*/

#define midichannel 0;
int speakerPin = 3;
unsigned char PadNote[8] = {60, 62, 64, 65, 67, 69, 71, 72};	 //array containing MIDI note values,

unsigned char status;
int PadCutOff[8] = {80, 110, 110, 110, 80, 110, 110, 110};	 //array containing "threshold" values;
                                                                 //increase (up to 1023) in order to make piezos less sensitive
int MaxPlayTime[8] = {90, 90, 90, 90, 90, 90, 90, 90};		 //time each note remains on after being hit

boolean activePad[8] = {0, 0, 0, 0, 0, 0, 0, 0};            // array of flags of pad currently playing
int PinPlayTime[8] = {0, 0, 0, 0, 0, 0, 0, 0};              // counter since pad started to play
boolean VelocityFlag = false;				    // set this variable to true if you'd like the volume
int analogPin = A0;                                         //to correspond to force of hit
int hitavg = 0;
int pad = 0;

byte byte1;
byte byte2;
byte byte3;

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
  Serial.begin(57600);
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
    hitavg = multiplex[pin];			//variable hitavg equals the voltage (0-1023) of the piezo
    pad = pin;
    if ((hitavg > PadCutOff[pin])) {		
      if ((activePad[pad] == false)) {	 
        if (VelocityFlag == true) {
          hitavg = (hitavg / 8) - 1;		
        }					//set voltage of piezo into volume (or "velocity") range of MIDI note (0-127)
        else {
          hitavg = 127;				//if you don't care, set velocity to max value (127)
        }
        playKey(144, PadNote[pad], hitavg);      //put together MIDI message; see - http://spikenzielabs.com/SpikenzieLabs/Serial_MIDI_files/Midi%20Message%20Ill2.png
        PinPlayTime[pad] = 0;			
        activePad[pad] = true;			
      }
      else {					
        PinPlayTime[pad] = PinPlayTime[pad] + 1;
      }
    }
    else if ((activePad[pad] == true)) { 	
      PinPlayTime[pad] = PinPlayTime[pad] + 1;
      if (PinPlayTime[pad] > MaxPlayTime[pad]) {	
        activePad[pad] = false;               
        playKey(128, PadNote[pad], 127); //128 is the "status" value which corresponds to an OFF state ()
      }
    }
  }
}


////////////////////////////////////////////////////////////////
// MAKE SOUND
////////////////////////////////////////////////////////////////
void playKey(unsigned char MESSAGE, unsigned char PITCH, unsigned char VELOCITY) {
  // MIDI_TX(MESSAGE,PITCH,VELOCITY);
  noTone(speakerPin);
  int duration = map(VELOCITY, 0, 127, 0, 1500);
  tone(speakerPin, PITCH, duration);
}

///////////////////////////
// If we get MIDI working...
///////////////////////////
void MIDI_TX(unsigned char MESSAGE, unsigned char PITCH, unsigned char VELOCITY) {
  status = MESSAGE + midichannel;
  Serial.print(status);
  Serial.print(PITCH);
  Serial.print(VELOCITY);
}
