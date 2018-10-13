
// //slow pulse 
// class SlowPulse : public Mode {
//   public:
//   SlowPulse (PixelPtr pixel, int delay = 40): Mode(pixel), delayValue(delay){}


//   virtual void modeSetup ()
//   {
//     for (uint8_t i = 0; i < loopLevels; i++)
//     {
//       Colour levelColour;
//       levelColour.r = (int)(((float)loopColour.r/(float)loopLevels)*(float)(loopLevels-i));
//       levelColour.g = (int)(((float)loopColour.g/(float)loopLevels)*(float)(loopLevels-i));
//       levelColour.b = (int)(((float)loopColour.b/(float)loopLevels)*(float)(loopLevels-i));
//       looptable[i] = levelColour;
//     } 
//   }
//   virtual void run ()
//   {

//     pulse();
//     delay(delayValue);
//   }
// protected:
//   void pulse()
//   {
//         if(index == 0){
//         forwards = true;
//       }
//       else if (index == loopLevels-1)
//       {
//         forwards = false;
//       }
//       forwards ? index++: index--;
//       setallPixels(looptable[index].r,looptable[index].g,looptable[index].b);
//   }
//   private:
//     int delayValue = 0;
//     static const Colour loopColour = {30,30,70};
//     static const int  loopLevels = PIXELCOUNT*2;
//     Colour looptable[loopLevels] ={};
//     int steps = loopLevels;
//     int index  = 0;
//     bool forwards = true;
// };

// //fast pulse
// class FastPulse : public SlowPulse
// {
//   public:
//    FastPulse(PixelPtr pixel): SlowPulse(pixel,10){}
// };

// //variable speed pulse
// class VariableSpeedPulse : public SlowPulse
// {
// public:
//   VariableSpeedPulse(PixelPtr pixel) : SlowPulse(pixel){}

//   virtual void run()
//   {
//     pulse();
//     if (m_delay == 10 && m_hold == 0)
//     {
//       forwards = true;
//       m_hold=100;
//     }
//     else if(m_delay == 100)
//     {
//       forwards = false;
//     }
//     if(m_hold>0)
//     {
//       m_hold--;
//     }
//     if(m_hold == 0)
//     {
//       (forwards? m_delay++ : m_delay--);
//     }
//     delay(m_delay);
//   }
//   private:
//     bool forwards = true;
//   uint8_t m_delay = 10;
//   uint8_t m_hold = 0;
// };