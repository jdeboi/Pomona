/**************************************************************************/
/* 
  EXERCISE:
  LED Accelerometer Turning Indicators
  March 2015
  Pomona College

  LEARNING OUTCOME:
  This exercise is designed to introduce I2C and accelerometers.

  CREDIT
  **License BSD - see license.txt**
  This sketch pulls from a library for the Adafruit MMA8451 Accel breakout
  ----> https://www.adafruit.com/products/2019
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit! Download the MMA8451 accelerometer library
  here: https://github.com/adafruit/Adafruit_MMA8451_Library
*/
/**************************************************************************/

#include <Wire.h>
#define MMA8451_DEFAULT_ADDRESS   0x1D
#define MMA8451_REG_OUT_X_MSB     0x01
#define MMA8451_REG_WHOAMI        0x0D
#define MMA8451_REG_XYZ_DATA_CFG  0x0E
#define MMA8451_REG_PL_STATUS     0x10
#define MMA8451_REG_PL_CFG        0x11
#define MMA8451_REG_CTRL_REG1     0x2A
#define MMA8451_REG_CTRL_REG2     0x2B
#define MMA8451_REG_CTRL_REG4     0x2D
#define MMA8451_REG_CTRL_REG5     0x2E
#define MMA8451_RANGE_4_G         0b01   // +/- 4g
#define MMA8451_RANGE_2_G         0b00   // +/- 2g (default value)

uint8_t _i2caddr;
int16_t x, y, z;
float x_g, y_g, z_g;

/**************************************************************************/

void setup() {
  // EXERCISE: fill out the setup
}

void loop() {
  // EXERCISE: fill out the setup
}

void checkForTurning() {
  // EXERCISE: fill out this function
  // if arm is raised, blink right; lowered, blink left
  // What values of getOrientation() correspond to these motions?
}

void blinkRightArrow() {
  // EXERCISE: fill out this function
  // blink at 0.5s intervals as long as hand is up/down
  // hint: millis() may come in handy (or interrupts- google!)
}

void blinkLeftArrow() {
  // EXERCISE: fill out this function
}

/**************************************************************************/

bool MMA8451Begin() {
  
  Wire.begin();
  _i2caddr = MMA8451_DEFAULT_ADDRESS;
  /* Check connection */
  uint8_t deviceid = readRegister8(MMA8451_REG_WHOAMI);
  if (deviceid != 0x1A) {
    /* No MMA8451 detected ... return false */
    return false;
  }
  writeRegister8(MMA8451_REG_CTRL_REG2, 0x40); // reset
  while (readRegister8(MMA8451_REG_CTRL_REG2) & 0x40);
  
  // EXERCISE: Enable 2g mode.
  writeRegister8(MMA8451_REG_XYZ_DATA_CFG, MMA8451_RANGE_4_G);
  
  writeRegister8(MMA8451_REG_CTRL_REG2, 0x02);  // High res
  writeRegister8(MMA8451_REG_CTRL_REG4, 0x01);  // Low noise!
  writeRegister8(MMA8451_REG_CTRL_REG4, 0x01);  // DRDY on INT1
  writeRegister8(MMA8451_REG_CTRL_REG5, 0x01);
  writeRegister8(MMA8451_REG_PL_CFG, 0x40);     // Turn on orientation config
  writeRegister8(MMA8451_REG_CTRL_REG1, 0x01);  // active, max rate
  return true;
}

void writeRegister8(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(_i2caddr);
  Wire.write((uint8_t)reg);
  Wire.write((uint8_t)(value));
  Wire.endTransmission();
}

uint8_t readRegister8(uint8_t reg) {
    Wire.beginTransmission(_i2caddr);
    Wire.write(reg);
    Wire.endTransmission(false); // MMA8451 + friends uses repeated start!!

    Wire.requestFrom(_i2caddr, 1);
    if (! Wire.available()) return -1;
    return (Wire.read());
}

void MMA8451Read() {
  // read x y z at once
  Wire.beginTransmission(_i2caddr);
  Wire.write(MMA8451_REG_OUT_X_MSB);
  Wire.endTransmission(false); // MMA8451 + friends uses repeated start!!

  Wire.requestFrom(_i2caddr, 6);
  x = Wire.read(); x <<= 8; x |= Wire.read(); x >>= 2;
  y = Wire.read(); y <<= 8; y |= Wire.read(); y >>= 2;
  z = Wire.read(); z <<= 8; z |= Wire.read(); z >>= 2;

  // EXERCISE: What is the divider in 2g mode? 4g mode? 8g?
  
  uint16_t divider = 1; // FILL IN CORRECT DIVIDER FROM DATA SHEET
  x_g = (float)x / divider;
  y_g = (float)y / divider;
  z_g = (float)z / divider;
  
  // EXERCISE: Print the acceleration.
}

uint8_t getOrientation() {
  return readRegister8(MMA8451_REG_PL_STATUS) & 0x07;
}


