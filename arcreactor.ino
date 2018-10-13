#include "arcreactor.h"

class LED {
  public:
   enum Action {
    stat,
    pulsing,
    fading,
    brightening,
  };

  LED(uint8_t id,  Action act, Adafruit_NeoPixel* pixel, uint16_t duration, Colour startCol, Colour endCol, boolean repeat = false ):
  m_id(id),
  m_act(act),
  m_pixel(pixel),
  m_duration(duration),
  m_startCol(startCol),
  m_endCol(endCol),
  m_repeat(repeat),
  m_start(millis()),
  m_running(true)
  {}

  void stepLED(){}

  private:
    uint8_t m_id = 0;
    Action m_act = stat;
    uint16_t m_duration = 0;
    uint16_t m_start = 0;
    Colour m_startCol = {};
    Colour m_endCol = {};
    bool m_repeat = false;
    bool m_running = false;
    PixelPtr m_pixel;
};

Mode::Mode(PixelPtr pixel): m_pixel(pixel)
{
  m_pixel->begin();
  m_pixel->show();
}

void Mode::runMode()
{
  if(error)
  {
    setallPixels(60,0,0);
    delay(1000000);
  }
  else
  {
    run();
  }
}
void Mode::setError() 
{
  error = true;
}

void Mode::setallPixels(uint8_t r, uint8_t g, uint8_t b)
{
  for(int i = 0; i < PIXELCOUNT; i++)
  {
    m_pixel->setPixelColor(i, r,g,b);
  }
  m_pixel->show();
}

void Static::modeSetup()
{
  setallPixels( 10,10,40);
}
void Static::run()
{
  delay(100000);
}

