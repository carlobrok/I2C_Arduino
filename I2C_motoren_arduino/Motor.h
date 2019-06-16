#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"

class Motor
{
  public:
    Motor(int pin_d, int pin_in1, int pin_in2, int pin_fb, int pin_sf);
    void 
      setupInterruptHandler(void (*ISR)(void), int value),
      vor(),
      vor(int speed),
      zurueck(),
      zurueck(int speed);
    float get_current();
 
  private:
    int _pin_d;
    int _pin_in1;
    int _pin_in2;
    int _pin_fb;
    int _pin_sf;
};

#endif
