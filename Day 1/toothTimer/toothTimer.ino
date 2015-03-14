/**************************************************************************/
/* 
  Teeth Brushing Timer
  March 2015
  Pomona College
  
  LEARNING OUTCOME:
  setup(), loop(), pinMode(), digitalWrite(), digitalRead(), analogWrite(), 
  delay(), millis(), for loops, while loops, if/else

*/
/**************************************************************************/

int time = 0;
int maxTime = 1000 * 60 * 2;

int buttonPin = 2;
int ledPin = 13;
// RGB pins - use PWM pins
int redPin = 3;
int greenPin = 5;
int bluePin = 6;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buttonPin, INPUT);
  
  time = maxTime;
}

void loop() {
  while(time > 0) {
    checkButton();
    time--;
    setRGBColor();
    delay(1);
  }
  /*
    for(time; time > 0; time++) {
      delay(1);
      setRGBColor();
      checkButton();
    }
  */
  blinkLED();
  checkButton();
}

void blinkLED() {
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  delay(500); 
}

void checkButton() {
  int reading = digitalRead(buttonPin);
  if(reading == HIGH) {
    resetTimer();
  }
}

void resetTimer() {
  time = maxTime;
}

void setRGBColor() {
  // Red 255, 0, 0
  // Yellow 255, 255, 0
  // Green 0, 255, 0
  if(time < maxTime/2) {
    int y = map(time, 0, maxTime/2, 0, 255);
    analogWrite(redPin, y);
    analogWrite(greenPin, 255);
    analogWrite(bluePin,0);
  }
  else {
    int y = map(time, maxTime/2, maxTime, 255, 0);
    analogWrite(redPin, 255);
    analogWrite(greenPin, y);
    analogWrite(bluePin,0);
  }
}
