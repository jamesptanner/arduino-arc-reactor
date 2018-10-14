
#ifndef DECAY_H
#define DECAY_H
#include "arcreactor.h"

class Animation;
class Decay : public Mode {
public:
    Decay(PixelPtr pixel): Mode(pixel){}
    void modeSetup();
    void run();
private:
    Animation* pixelAnimation[PIXELCOUNT];
    static const int chanceOptions = 5;

    const int chances[chanceOptions]{
        120, // dead
        30,  // solid 
        15,  // pulse
        20, // OnOff
    };

    // DONT FORGET TO UPDATE IF THE TABLE CHANGES.

    long chanceTotal=185;
};

class Animation 
{
public:
    Animation(PixelPtr p, uint8_t pixelId, uint16_t d) : m_pixel(p), m_pixelId(pixelId), duration(d) {}
    virtual ~Animation(){}
    virtual void animationSetup() = 0;
    void step();
    bool isRunning() {return running;}
protected:
    void setallPixels(uint8_t r, uint8_t g, uint8_t b);
    virtual void animationStep() = 0;
    uint8_t m_pixelId;
    uint16_t frame = 0;
    uint16_t duration;
    bool running = true;
    PixelPtr m_pixel;
};

class Dead : public Animation 
{
    public:
    Dead(PixelPtr p,int pixelId, bool init = false) : Animation(p, pixelId, init?0:random(80,500)){}
    virtual ~Dead(){}
    void animationStep();
    void animationSetup();
};

class AnimSolid : public Animation
{
    public:
    AnimSolid(PixelPtr p,int pixelId) : Animation(p, pixelId, random(50,500)){}
    virtual ~AnimSolid(){}
    void animationStep();
    void animationSetup();
};

class AnimPulse : public Animation
{
    private:
        uint8_t pulseDuration; //halfcycle
        uint8_t numberOfPulses;
        bool forwards = true;
        Colour maxColour = {80,0,0};

    public:
        AnimPulse(PixelPtr p,int pixelId) : numberOfPulses(random(5,9)), pulseDuration(random(300,500)), Animation(p, pixelId,pulseDuration*numberOfPulses){}
        virtual ~AnimPulse(){}
        void animationStep();
        void animationSetup();
};

class OnOff : public Animation
{
    public:
    OnOff(PixelPtr p,int pixelId) : Animation(p, pixelId,random(200,300)){}
    virtual ~OnOff(){}
    void animationStep();
    void animationSetup();
};

#endif