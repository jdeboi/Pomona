/*
The following code will help you get started in controlling your own “zero emissions” electric car.
It requires a H-Bridge driver that allows you to control the current flowing through the motors. 
The PWM (pulse width modulation) pins 3,5,6, and 9 allows you to use the analogWrite command to control 
the speed of the motors. The other pins are used to enable and disable the necessary H-bridge components 
so that you are not trying to move the motors in two directions at the same time.

*/

int leftEn = 4;//enable left motor
int leftFor = 5;//left motor forward
int leftRev = 3;//left motor reverse
int rightEn = 7;//enable right motor
int rightFor = 9;//right motor forward
int rightRev = 6;//right motor reverse
  
  
void setup()
{
  //EXERCISE: fill out
  //A high on enable will allow it to run  
}


void loop() 
{
  turnLeft();
  delay (5000);
  turnRight();
  delay (5000);
  goStraight();
  delay (5000);
  goBack();
  delay (5000);
  goFast();
  delay (5000);
  goBackfast();
  delay(5000);
}


void turnLeft()
{
  //EXERCISE: fill out
}


void turnRight()
{
  //EXERCISE: fill out
}
  
void goStraight()
{
  //EXERCISE: fill out
}

void goBack()
{
  //EXERCISE: fill out
}

void goFast()
{
  //EXERCISE: fill out
}
  
void goBackfast()
{
  //EXERCISE: fill out
}
  
  
