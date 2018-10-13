
#ifndef SPINNER_H
#define SPINNER_H

#include "arcreactor.h"

class Spinner : public Mode
{
  private:
  static const int loopTrails = 3;
  static const Colour loopColour = {20,20,40};
  static const int  loopLevels = PIXELCOUNT / loopTrails;
  Colour looptable[loopLevels] ={};
  int spinStep =0;
public:

  Spinner(PixelPtr pixel, int loopDelay= 10) : Mode(pixel), m_loopDelay(loopDelay){}
  virtual void modeSetup();


  virtual void run();
  protected: 

  int spinIndex = 0 ;
  void spin();
  private:
  int m_loopDelay = 0;
};

class SlowSpinner: public Spinner{
  public:
  SlowSpinner(PixelPtr pixel) : Spinner(pixel,40){}
};

//spinning faster then slower.
class VarSpeedSpinner : public Spinner
{
public:
  VarSpeedSpinner(PixelPtr pixel): Spinner(pixel){}
  virtual void modeSetup(){
    Spinner::modeSetup();
  }
  virtual void run();
private:
  bool forwards = true;
  uint8_t m_delay = 10;
  uint8_t m_hold = 0;
};
#endif