
#ifndef ARCREACTOR_H
#define ARCREACTOR_H
#include <Adafruit_NeoPixel.h>

#define PIXELPIN 7
#define PIXELCOUNT 24

typedef Adafruit_NeoPixel* PixelPtr;

struct Colour {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

class Mode
{
  public:
  
  Mode(PixelPtr pixel);
  virtual void modeSetup(){}
  virtual void run() = 0;
  void runMode();
protected:
  void setError() ;
  void setallPixels(uint8_t r, uint8_t g, uint8_t b);
  PixelPtr m_pixel;

private:
  bool error = false;
};

class Static : public Mode
{
  public:
  Static(PixelPtr pixel): Mode(pixel){}
  virtual void modeSetup();
  virtual void run();
};
#endif