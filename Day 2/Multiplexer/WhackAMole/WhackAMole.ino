/**************************************************************************/
/* 
  Arduino Whack A Mole
  March 2015
  Pomona College
  Jenna deBoisblanc (http://jdeboi.com)
  
  LEARNING OUTCOME:
  This exercise is designed to introduce multiplexers.
  
*/
/**************************************************************************/

#include <toneAC.h>

int analogPin = 0;
int moleLEDPins[8];
int moleStates[8];
int hitThresh[8];
int moleNote[8];
boolean volumeOn = true;
int pause = 1000;
int duration = 2000;
int lastUpdate = 0;
int lives = 5;
int score = 0;

int r0 = 0;      //value of select pin at the 4051 (s0)
int r1 = 0;      //value of select pin at the 4051 (s1)
int r2 = 0;      //value of select pin at the 4051 (s2)
int count = 0;   //which y pin we are selecting

int multiplex[8];

void setup() {
  
}

void loop() {
  setMoleStates();
  checkPiezos();
  updateMoleStates();
  updateLEDStates();
}

void setMoleStates() {

}

void updateMoleStates() {

}

void checkPiezos() {
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
    if(multiplex[count] > hitThresh[count]) hit(count, multiplex[count]);
  }
}

void hit(int num, int force) {
  
}

void updateLEDStates() {
  
}

void lostSequence() {
  
}

void blinkLEDs() {

}

void playKey(int freq, int force) {

}
