#include "decay.h"
#include "Arduino.h"
void Decay::modeSetup()
{
    setallPixels(0,0,0);
    //init all animations so we dont have to deal with nulls in the first run.
    for (int i = 0; i < PIXELCOUNT; i++)
    {
        pixelAnimation[i] = new AnimSolid(m_pixel,i);
        pixelAnimation[i]->animationSetup();
    }
}

void Decay::run()
{
    //step animations and then check for completed and replace.
    for (int animationIndex = 0; animationIndex < PIXELCOUNT; animationIndex++)
    {
        pixelAnimation[animationIndex]->step();
        if(!pixelAnimation[animationIndex]->isRunning())
        {
        //    Serial.print("resetting animation ");
          //  Serial.println(animationIndex);
            delete pixelAnimation[animationIndex];
            //time to replace. and setup.
            m_pixel->setPixelColor(animationIndex,0,0,0);
            int chance = random(0,chanceTotal);
            for (int chanceIndex = 0; chanceIndex < chanceOptions; chanceIndex++)
            {
              //  Serial.print("Using mode ");
                if(chance < chances[chanceIndex]){
                    if(chanceIndex == 0){
                        Serial.println("Dead");
                        pixelAnimation[animationIndex] = new Dead(m_pixel,animationIndex);
                    }
                    else if(chanceIndex == 1){
            //            Serial.println("Solid");
                        pixelAnimation[animationIndex] = new AnimSolid(m_pixel,animationIndex);
                    }
                    else if(chanceIndex == 2){
            //            Serial.println("fizzle");
                        pixelAnimation[animationIndex] = new Fizzle(m_pixel,animationIndex);
                    } 
                    else if(chanceIndex == 3){
         //               Serial.println("pulse");
                        pixelAnimation[animationIndex] = new AnimPulse(m_pixel,animationIndex);
                    }
                    pixelAnimation[animationIndex]->animationSetup();

                    break;
                }
                else chance -= chances[chanceIndex];
            }
        }
    } 
    m_pixel->show();
    delay(5);
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


void Dead::animationStep(){m_pixel->setPixelColor(m_pixelId, 0,0,0);}
void Dead::animationSetup(){}

void AnimSolid::animationStep(){
    m_pixel->setPixelColor(m_pixelId, 30,0,0);
}
void AnimSolid::animationSetup(){} 

void Fizzle::animationStep(){}
void Fizzle::animationSetup(){m_pixel->setPixelColor(m_pixelId, 0,60,30);}

void AnimPulse::animationStep(){}
void AnimPulse::animationSetup(){m_pixel->setPixelColor(m_pixelId, 0,0,30);}

void OnOff::animationStep(){}
void OnOff::animationSetup(){m_pixel->setPixelColor(m_pixelId, 0,30,0);}