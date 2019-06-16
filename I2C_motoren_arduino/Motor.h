#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"

#define MOTOR_LEFT 0
#define MOTOR_RIGHT 1
#define MOTOR_BOTH 2

#define MOTOR_FORWARD 0
#define MOTOR_BACKWARD 1
#define MOTOR_OFF 2

class Motor
{
  public:
    Motor(int pin_d, int pin_in1, int pin_in2, int pin_fb, int pin_sf);
    void 
      setupInterruptHandler(void (*ISR)(void), int value),
      vor(),
      vor(int speed),
      zurueck(),
      zurueck(int speed),
      aus();
    float get_current();
 
  private:
    int _pin_d;
    int _pin_in1;
    int _pin_in2;
    int _pin_fb;
    int _pin_sf;
};

#endif
