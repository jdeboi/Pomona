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
int moleLEDPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
int moleStates[] = {0, 0, 0, 0, 0, 0, 0 , 0};
int hitThresh[] = {110, 110, 110, 110, 110, 110, 110, 110};
int moleNote[] = { 262, 196, 196, 220, 196, 0, 247, 262 };
boolean velocityOn = true;
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
  lastUpdate = millis();
  delay(1500);
  Serial.begin(9600);
  for(int i = 0; i < 8; i++) {
    pinMode(moleLEDPins[i], OUTPUT);
  }
}

void loop() {
  setMoleStates();
  checkPiezos();
  updateMoleStates();
  updateLEDStates();
}

void setMoleStates() {
  if(millis() - lastUpdate > pause) {
    int randNum = int(random(8));
    if(moleStates[randNum] == 0) {
      moleStates[randNum] = millis();
      lastUpdate = millis();
      pause-=10;
      duration-=5;
    }
  }
}

void updateMoleStates() {
  for(int i = 0; i < 8; i++) {
    if(moleStates[i] > 0) {
      if (millis() - moleStates[i] > duration) {
        moleStates[i] = 0;
        lives--;
        if(lives == 0) lostSequence();
      }
    }  
  }
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
  if(moleStates[num] > 0) {
    score+= 100;
    moleStates[num] = 0;
    playKey(moleNote[num],force);
  }
}

void updateLEDStates() {
  for(int i = 0; i < 8; i++) {
    if(moleStates[i] > 0) digitalWrite(moleLEDPins[i], HIGH);
    else digitalWrite(moleLEDPins[i], LOW);
  }
}

void lostSequence() {
  blinkLEDs();
  blinkLEDs();
  Serial.println("Your score is: " + score);
  while(1);
}

void blinkLEDs() {
  for(int i = 0; i < 8; i++) {
    digitalWrite(moleLEDPins[i], HIGH);
  }
  delay(500);
  for(int i = 0; i < 8; i++) {
    digitalWrite(moleLEDPins[i], LOW);
  }
  delay(500);
}

void playKey(int freq, int velocity) {
  if (velocityOn == true) {
    velocity = velocity / 100;		
  }					
  else {
    velocity = 10;  
  }
  noToneAC();
  int duration = map(velocity, 0, 1023, 0, 500);
  toneAC(freq, velocity, duration, true);
}
