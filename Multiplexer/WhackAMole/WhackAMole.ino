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
int analogPin = 0;
int moleLEDPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
int moleStates[] = {0, 0, 0, 0, 0, 0, 0 , 0};
int pause = 1000;
int duration = 1000;
int lastUpdate = 0;

void setup() {
  // put your setup code here, to run once:
  lastUpdate = millis();
  delay(1500);
}

void loop() {
  // put your main code here, to run repeatedly:
  setStates();
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
  }
}

void setStates() {
  if(millis() - lastUpdate > pause) {
    int randNum = random(8);
    if(moleStates[randNum] == 0) {
      moleStates[randNum] = duration;
      lastUpdate = millis();
      pause--;
      duration--;
    }
  }
}

void updateStates() {
  for(int i = 0; i < moleStates.length; i++) {
    if(moleStates[i] > 0) moleStates[i]--;
  }
}

