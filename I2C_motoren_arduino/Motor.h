#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"

// WHAT TO DO
#define MOTOR_DIR_PWM 0
#define MOTOR_DIR_PWM_BOTH 1
#define MOTOR_STATE 2

// WICH MOTOR
#define MOTOR_LEFT 0
#define MOTOR_RIGHT 1
#define MOTOR_BOTH 2

// WICH DIRECTION
#define MOTOR_FORWARD 0
#define MOTOR_BACKWARD 1

// WICH MOTOR STATE
#define MOTOR_OFF 1
#define MOTOR_FORWARD_NORMAL 2
#define MOTOR_BACKWARD_NORMAL 3


class Motor
{
  public:
    Motor(int pin_d, int pin_in1, int pin_in2, int pin_fb, int pin_sf);
    void 
      setupInterruptHandler(void (*ISR)(void), int value),
      update(int direction, int speed),
      update(int state);
    float get_current();

  private:
    void 
      vor(),
      vor(int speed),
      zurueck(),
      zurueck(int speed),
      aus();
  
    int _direction;
    int _speed;
    
    int _pin_d;
    int _pin_in1;
    int _pin_in2;
    int _pin_fb;
    int _pin_sf;
};

#endif
