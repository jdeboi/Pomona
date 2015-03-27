/*
This is short demo program to show how the range finder works with the Arduino.
There’s only two I/O pins echo, and trigger. 
This program is configured to turn on a LED with something is within 2 inches of the sensor.
*/

const int pingPin = 7;
const int start_signal = 8;
long inches, duration;
void setup()
{
  Serial.begin(9600);
}

void loop()
{
  rangeCheck();
  if (inches < 2)
  {
    digitalWrite (3, HIGH);
  }
  else 
  {
    digitalWrite (3, LOW);
  }
}
void rangeCheck()
{
  
  pinMode(pingPin, OUTPUT);
  pinMode(start_signal, OUTPUT);
  digitalWrite(start_signal, HIGH);
  delayMicroseconds(20);
  digitalWrite(start_signal, LOW);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  inches = microsecondsToInches(duration);
   
  Serial.print(inches);
  Serial.print("in, ");
  
  delay(80);
}
long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}

