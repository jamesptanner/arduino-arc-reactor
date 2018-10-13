
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

    const int chances[5]{
        50, // dead
        5,  // solid 
        10, // fizzle
        3,  // pulse
        20, // OnOff
    };

    // DONT FORGET TO UPDATE IF THE TABLE CHANGES.
    const int chanceOptions = sizeof (chances) / sizeof(int);
    const long chanceTotal = 83;
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
    Dead(PixelPtr p,int pixelId, bool init = false) : Animation(p, pixelId, init?0:random(80,150)){}
    ~Dead(){}
    void animationStep();
    void animationSetup();
};

class AnimSolid : public Animation
{
    public:
    AnimSolid(PixelPtr p,int pixelId) : Animation(p, pixelId, random(50,500)){}
    ~AnimSolid(){}
    void animationStep();
    void animationSetup();
};

class Fizzle : public Animation
{
    public:
    Fizzle(PixelPtr p ,int pixelId): Animation(p, pixelId, random(40,300)){}
    ~Fizzle(){}
    void animationStep();
    void animationSetup();
};

class AnimPulse : public Animation
{
    public:
    AnimPulse(PixelPtr p,int pixelId) : Animation(p, pixelId,random(30,700)){}
    ~AnimPulse(){}
    void animationStep();
    void animationSetup();
};

class OnOff : public Animation
{
    public:
    OnOff(PixelPtr p,int pixelId) : Animation(p, pixelId,random(200,300)){}
    ~OnOff(){}
    void animationStep();
    void animationSetup();
};

#endif