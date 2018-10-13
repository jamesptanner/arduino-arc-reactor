
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

    static const int chances[5]{
        100, // dead
        5,  // solid 
        10, // fizzle
        3,  // pulse
        20, // OnOff
    };

    // DONT FORGET TO UPDATE IF THE TABLE CHANGES.
    static const int chanceOptions = sizeof (chances) / sizeof(int);
    static const long chanceTotal = 138;
};

class Animation 
{
public:
    Animation(PixelPtr p, uint16_t d) : pixel(p), duration(d) {}
    virtual void animationSetup() = 0;
    void step();
    bool isRunning() {return running;}
protected:
    virtual void animationStep() = 0;
    uint8_t pixelId;
    uint16_t frame = 0;
    uint16_t duration;
    bool running = true;
    PixelPtr pixel;
};

class Dead : public Animation 
{
    public:
    Dead(PixelPtr p,bool init = false) : Animation(p,init?0:100){}
    void animationStep();
    void animationSetup();
};

class AnimSolid : public Animation
{
    public:
    AnimSolid(PixelPtr p) : Animation(p,100){}
    void animationStep();
    void animationSetup();
};

class Fizzle : public Animation
{
    public:
    Fizzle(PixelPtr p ): Animation(p,40){}
    void animationStep();
    void animationSetup();
};

class AnimPulse : public Animation
{
    public:
    AnimPulse(PixelPtr p) : Animation(p,30){}
    void animationStep();
    void animationSetup();
};

class OnOff : public Animation
{
    public:
    OnOff(PixelPtr p) : Animation(p,30){}
    void animationStep();
    void animationSetup();
};

#endif