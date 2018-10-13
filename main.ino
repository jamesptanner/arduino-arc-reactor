#include <EEPROM.h>

#include "pulse.h"
#include "spinner.h"
#include "decay.h"

const uint8_t modeCount = 6;
uint8_t mode;
//*******************************************************************************************
//                                arduino functions
//*******************************************************************************************
Mode* currentMode;
void setup() {
  // setup random numbers
  randomSeed(analogRead(0));
  
  //initilaize the pixels

  //increment the counter and loop around if needed
  mode = EEPROM.read(0);
  EEPROM.write(0,(mode+1)%modeCount);
  //mode = 7;
  PixelPtr pixel = new Adafruit_NeoPixel(PIXELCOUNT,PIXELPIN);
  if(mode == 0)
  {
    currentMode = new Static(pixel);
  }
  else if (mode == 1)
  {
    currentMode = new Spinner(pixel);
  }
  else if (mode == 2)
  {
    currentMode = new VarSpeedSpinner(pixel);
  }
  else if (mode == 3)
  {
    currentMode = new SlowPulse(pixel);
  }
  else if (mode == 4)
  {
    currentMode = new FastPulse(pixel);
  }
  else if (mode == 5)
  {
    currentMode = new VariableSpeedPulse(pixel);
  }
  else if (mode == 6)
  {
    currentMode = new SlowSpinner(pixel);
  }
  else if (mode == 7)
  {
      //currentMode = new Decay(pixel);
  }
  //run specific setup for the mode.
  currentMode->modeSetup();
  delay(100);
  Serial.begin(9600);

}

void loop() {
  currentMode->runMode();
}