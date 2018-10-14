#include "decay.h"
#include "Arduino.h"
#include "MemoryFree.h"
void Decay::modeSetup()
{
    setallPixels(0,0,0);
    //init all animations so we dont have to deal with nulls in the first run.
    for (int i = 0; i < PIXELCOUNT; i++)
    {
        pixelAnimation[i] = new Dead(m_pixel,i,true);
        pixelAnimation[i]->animationSetup();
    }
}

void Decay::run()
{
    //step animations and then check for completed and replace.
    for (int animationIndex = 0; animationIndex < PIXELCOUNT; animationIndex++)
    {
        pixelAnimation[animationIndex]->step();
        if(pixelAnimation[animationIndex]==NULL ||!pixelAnimation[animationIndex]->isRunning())
        {
        //    Serial.print("resetting animation ");
          //  Serial.println(animationIndex);
            if(pixelAnimation[animationIndex]!=NULL)
            {
                delete pixelAnimation[animationIndex];
            }
            //time to replace. and setup.
            m_pixel->setPixelColor(animationIndex,0,0,0);
            int chance = random(0,chanceTotal-1);
            for (int chanceIndex = 0; chanceIndex < chanceOptions; chanceIndex++)
            {
              //  Serial.print("Using mode ");
                // Serial.print("freeMemory()=");
                // Serial.println(freeMemory());
                if(chance < chances[chanceIndex]){
                    if(chanceIndex == 0){
                        //Serial.println("Dead");
                        pixelAnimation[animationIndex] = new Dead(m_pixel,animationIndex);
                    }
                    else if(chanceIndex == 1){
            //            Serial.println("Solid");
                        pixelAnimation[animationIndex] = new AnimSolid(m_pixel,animationIndex);
                    }
                    else if(chanceIndex == 2){
         //               Serial.println("pulse");
                        pixelAnimation[animationIndex] = new AnimPulse(m_pixel,animationIndex);
                    }
                    else if(chanceIndex == 3){
         //               Serial.println("pulse");
                        pixelAnimation[animationIndex] = new OnOff(m_pixel,animationIndex);
                    }
                    else {
                        //Serial.println("onoff")
                        pixelAnimation[animationIndex] = new Dead(m_pixel,animationIndex);
                    }
                    pixelAnimation[animationIndex]->animationSetup();

                    break;
                }
                else chance -= chances[chanceIndex];
            }
        }
    } 
    m_pixel->show();
    delay(1);
}

void Animation::step()
{
    animationStep();
    frame++;
    if (frame >= duration)
    {
        running = false;
    }
}


void Dead::animationSetup(){}
void Dead::animationStep(){m_pixel->setPixelColor(m_pixelId, 0,0,0);}

void AnimSolid::animationSetup(){} 
void AnimSolid::animationStep(){
    m_pixel->setPixelColor(m_pixelId, 30,0,0);
}

void OnOff::animationSetup(){}
void OnOff::animationStep(){
    if(frame % random(0,23) == 0)
    {
        m_pixel->setPixelColor(m_pixelId,random()%2 ? 40:0,0,0);
    }
}

void AnimPulse::animationSetup(){}
void AnimPulse::animationStep(){
        uint8_t currentFrame = frame % pulseDuration;

    Colour sendColour = {};
    uint8_t effectiveFrame = forwards ? currentFrame :  pulseDuration - currentFrame;
    sendColour.r = (int)(((float) maxColour.r / (float) pulseDuration) * (float) effectiveFrame);
    sendColour.g = (int)(((float) maxColour.g / (float) pulseDuration) * (float) effectiveFrame);
    sendColour.b = (int)(((float) maxColour.b / (float) pulseDuration) * (float) effectiveFrame);

    m_pixel->setPixelColor(m_pixelId,sendColour.r,sendColour.g,sendColour.b);
    if( currentFrame == pulseDuration - 1)  
    {
        forwards = !forwards;
    }
}

