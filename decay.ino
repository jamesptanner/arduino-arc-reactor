#include "decay.h"


void Decay::modeSetup()
{
    setallPixels(0,0,0);
    //init all animations so we dont have to deal with nulls in the first run.
    for (int i = 0; i < PIXELCOUNT; i++)
    {
        pixelAnimation[i] = new Dead(m_pixel,true);
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
            //time to replace. and setup.
            m_pixel->setPixelColor(animationIndex,0,0,0);
            long chance = 0;//random(chanceTotal);
            for (int chanceIndex = 0; chanceIndex < chanceOptions; chanceIndex++)
            {
                delete pixelAnimation[animationIndex];
                if(chance < chances[chanceIndex]){
                    if(chanceIndex == 0){
                        pixelAnimation[animationIndex] = new Dead(m_pixel);
                    }
                    else if(chanceIndex == 1){
                        pixelAnimation[animationIndex] = new AnimSolid(m_pixel);
                    }
                    else if(chanceIndex == 2){
                        pixelAnimation[animationIndex] = new Fizzle(m_pixel);
                    } 
                    else if(chanceIndex == 3){
                        pixelAnimation[animationIndex] = new AnimPulse(m_pixel);
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


void Dead::animationStep(){}
void Dead::animationSetup(){}

void AnimSolid::animationStep(){}
void AnimSolid::animationSetup(){} 

void Fizzle::animationStep(){}
void Fizzle::animationSetup(){}

void AnimPulse::animationStep(){}
void AnimPulse::animationSetup(){}

void OnOff::animationStep(){}
void OnOff::animationSetup(){}