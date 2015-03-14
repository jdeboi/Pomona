/**************************************************************************/
/* 
  Arduino Tea Kettle Alarm
  March 2015
  Pomona College
  
  LEARNING OUTCOME:
  analogRead(), libraries, Serial Monitor, while loops, thermistor circuits

*/
/**************************************************************************/
#include <toneAC.h>

int thermPin = A0;
int ledPin = 13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  if(getTemperature() > 100) {
    while(1) blinkLED();
    //whistle(300);
    //turnOffKettle();
  }
}

int getTemperature() {
  int reading = analogRead(thermPin);
  Serial.println(reading);
  
  // temperature calibration goes here
  int temp = reading/100;
}

void blinkLED() {
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  delay(500); 
}

void whistle(int freq) {
  // freq, vel, dur, background
  for(int i = 0; i < 10; i++) {
    toneAC(freq, i+1, 100, false);
  }
  toneAC(freq, 10, 500, false);
  while(1);
}
