/**************************************************************************/
/*!
    @file     dwightbop.ino
    @author   D. Whitaker (Pomona College) 
    This program is an Arduino game that uses the Adafruit MMA 8451 accelerometer and their drivers.  A random color is lit on the tricolor 
   LED and you have to orient the board based on the color.  For our case the board should be upright and tall for red, tilted 
   to the left for green, and tilted to the right for blue.  For each correct answer the time to react decreases.  
   
   A high score is recorded and scores that exceed it are indicated by a high short beep.
   
    v1.0  - First release
*/
/**************************************************************************/

#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

Adafruit_MMA8451 mma = Adafruit_MMA8451();

// Define some pins for the tricolor LED.  We use a common anode LED, so LOW is on.

const int RedLED = 2;
const int GreenLED = 3;
const int BlueLED = 4;


int randNumber=0;
int time = 2000; /*This is the initial response time */
int timestep = 50; // The amount we decrease the response time with each correct response
int score = 0; //your current streak of right orientations
int hiscore = 0; // the high score (initialized to zero)

void setup(void) {
  pinMode(RedLED, OUTPUT);
  pinMode(GreenLED, OUTPUT);
  pinMode(BlueLED, OUTPUT);
  
  Serial.begin(9600);
  
 //Here we test communications to the accelerometer 
  Serial.println("Adafruit MMA8451 test!");
  

  if (! mma.begin()) {
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("MMA8451 found!");
  
  mma.setRange(MMA8451_RANGE_2_G);

//since we are using the orientation functions, the accelerometer range is not important.
  
  Serial.print("Range = "); Serial.print(2 << mma.getRange());  
  Serial.println("G");
  
}

void loop() {

//Display a random color 1 = green, 2 = red, 3 = blue
 
}
//  uint8_t o = mma.getOrientation();
//  
//  switch (o) {
//    case MMA8451_PL_PUF: 
//      Serial.println("Portrait Up Front");
//      break;
//    case MMA8451_PL_PUB: 
//      Serial.println("Portrait Up Back");
//      break;    
//    case MMA8451_PL_PDF: 
//      Serial.println("Portrait Down Front");
//      break;
//    case MMA8451_PL_PDB: 
//      Serial.println("Portrait Down Back");
//      break;
//    case MMA8451_PL_LRF: 
//      Serial.println("Landscape Right Front");
//      break;
//    case MMA8451_PL_LRB: 
//      Serial.println("Landscape Right Back");
//      break;
//    case MMA8451_PL_LLF: 
//      Serial.println("Landscape Left Front");
//      break;
//    case MMA8451_PL_LLB: 
//      Serial.println("Landscape Left Back");
//      break;
//    }
//  Serial.println();
//  delay(500);
  

