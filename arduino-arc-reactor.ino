#include <EEPROM.h>

#include "pulse.h"
#include "spinner.h"
#include "decay.h"
#include "MemoryFree.h"

const uint8_t modeCount = 8;
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
  //mode = EEPROM.read(0);
  //EEPROM.write(0,(mode+1)%modeCount);
  mode = 7;

  PixelPtr pixel = new Adafruit_NeoPixel(PIXELCOUNT,PIXELPIN);
#define DEBUG
#ifdef DEBUG
for (int i = 0 ; i < mode ; i ++)
{
  pixel->setPixelColor(i,0,40,0);
  delay(100);
}
  pixel->begin();
  pixel->show();
  Serial.begin(38400);
 while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
#endif
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
      currentMode = new Decay(pixel);
  }
  //run specific setup for the mode.
  currentMode->modeSetup();
  delay(100);
  Serial.print("reboot : mode ");
  Serial.println(mode);
}

void loop() {
  
  //Serial.println("Hello World");
  delay(10);
  currentMode->runMode();
   //Serial.print("freeMemory()=");
    //Serial.println(freeMemory());
}