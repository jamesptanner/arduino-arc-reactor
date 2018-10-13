
#include "spinner.h"

void Spinner::modeSetup()
{
    for (uint8_t i = 0; i < loopLevels; i++)
    {
        Colour levelColour;
        levelColour.r = (loopColour.r/loopLevels)*(loopLevels-i);
        levelColour.g = (loopColour.g/loopLevels)*(loopLevels-i);
        levelColour.b = (loopColour.b/loopLevels)*(loopLevels-i);
        looptable[i] = levelColour;
    } 
    if(PIXELCOUNT % loopTrails){
        setError();
    }
}


void Spinner::run()
{
    // a chase sequence with n levels high -> low where PIXELCOUNT % loopTrail == 0
    // each step shifts all the values around

    spin();
    delay(m_loopDelay);
}

void Spinner::spin()
{
    spinIndex++;
    delay (10);
    int levels = PIXELCOUNT / loopTrails;
    for (uint8_t i =0 ; i < PIXELCOUNT; i++)
    {
        Colour ourcol = looptable[(i+spinIndex)%(loopLevels)] ;
        m_pixel->setPixelColor(i,ourcol.r,ourcol.g,ourcol.b);
    }
    m_pixel->show();
}

void VarSpeedSpinner::run()
{
    spin();
    if (m_delay == 10 && m_hold == 0)
    {
        forwards = true;
        m_hold=160;
    }
    else if(m_delay == 75)
    {
        forwards = false;
    }
    if(m_hold>0)
    {
        m_hold--;
    }
    if(m_hold == 0)
    {
        (forwards? m_delay++ : m_delay--);
    }
    delay(m_delay);
}