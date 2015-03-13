/*
* Autonomous, Edge-Finding Car
* March 2015
* Pomona College
*
* This exercise is designed to introduce H-Bridges and DC Motors.
*
*/

// LESSON: How to use H-Bridge
// use PWM pins for motor control
const int motor1Pin1 = 3;    // H-bridge pin 2, 1A
const int motor1Pin2 = 5;    // H-bridgepin 7, 2A
const int motor2Pin1 = 6;    // H-bridge pin 10, 3A
const int motor2Pin2 = 9;    // H-bridge pin 15, 4A
const int enablePin = 4;    // H-bridge enable pin

int analogMotorVoltage = 50;
int maxDelay = 500;

// pins for the ultrasonic sensor
int trigPin = 13;
int echoPin = 12;

void setup() {
  Serial.begin (9600);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enablePin, OUTPUT);
 
  startCar();
}

void loop() {
  
  // determine distance with ultrasonic sensor
  long duration, distance;
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // pulseIn counts the time (in microseconds) it takes for echoPin to go HIGH
  duration = pulseIn(echoPin, HIGH);
  // distance = rate * time = speed of sound * t = (1/29.1 cm/microseconds) * t
  // divide time by two since the sound travels there and back
  distance = (duration/2) / 29.1;
  Serial.print(distance);
  Serial.println(" cm");
  
  if (distance >= 10 || distance <= 0){
    stopCar();
    turnInPlace(90);
  }
  else {
    moveCar(10);
  }
}

// EXERCISE: Write this function
void turnInPlace(int rotation) {
  // turn motor for a specified amount of time
  int turnTime = map(abs(rotation)%360, 0, 360, 0, maxDelay);
  // OR turn motor at a specific voltage to maxVoltage (if that equals a full rotation)
  // int turnTime = map(abs(rotation)%360, 0, 360, 0, maxVoltage);
  startCar();
  if(rotation < 0) {
    turnInPlaceLeft(analogMotorVoltage);
    delay(turnTime); 
    stopCar();  
  }
  else {
    turnInPlaceRight(analogMotorVoltage);
    delay(turnTime);  
    stopCar();  
  }
}

void turnInPlaceLeft(int volts) {
  // EXERCISE: Write this function
  // LESSON: How to get car to turn in place
  analogWrite(motor1Pin1, 0);   // set leg 1 of the H-bridge low
  analogWrite(motor1Pin2, volts);  // set leg 2 of the H-bridge high 
  // move motors in opposite directions
  analogWrite(motor2Pin1, volts);  
  analogWrite(motor2Pin2, 0);
}

void turnInPlaceRight(int volts) {
  // EXERCISE: Write this function
  analogWrite(motor1Pin1, volts);  
  analogWrite(motor1Pin2, 0); 
  analogWrite(motor2Pin1, 0); 
  analogWrite(motor2Pin2, volts);
}

void startCar() {
  // EXERCISE: Write this function
  // set enablePin high so that motor can turn on:
  digitalWrite(enablePin, HIGH);
}

void stopCar() {
  // EXERCISE: Write this function
  digitalWrite(enablePin, LOW);
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}

void moveCar(int carVelocity) {
  // EXERCISE: Write this function
  // how long, how fast
  if(carVelocity > 0) moveForward(carVelocity%255);
  else moveBackward(abs(carVelocity)%255);
}

void moveForward(int carSpeed) {
  analogWrite(motor1Pin1, carSpeed);  
  analogWrite(motor1Pin2, 0); 
  analogWrite(motor2Pin1, carSpeed); 
  analogWrite(motor2Pin2, 0);
}

void moveBackward(int carSpeed) {
  analogWrite(motor1Pin1, 0);  
  analogWrite(motor1Pin2, carSpeed); 
  analogWrite(motor2Pin1, 0); 
  analogWrite(motor2Pin2, carSpeed);
}
