#include <Wire.h>
#include "Motor.h"

#define SERIAL_OUTPUT

Motor motorLeft(5, 7, 8, A0, 2);
Motor motorRight(6, 9, 10, A1, 3);


void setup() {
  Wire.begin(0x08);
  Wire.onReceive(receiveEvent);

  pinMode(LED_BUILTIN, OUTPUT);

#ifdef SERIAL_OUTPUT
  Serial.begin(115200);
#endif
}

void loop() {

  // Motoren ansteuern

  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(3000 - 100);
}

void receiveEvent(int byte_amount) {

  digitalWrite(LED_BUILTIN, HIGH);

#ifdef SERIAL_OUTPUT
  Serial.print("Anzahl: ");
  Serial.println(byte_amount);
#endif

  while (Wire.available() > 3) {
#ifdef SERIAL_OUTPUT
    Serial.print(Wire.read());
    Serial.print(" ");
#else
    Wire.read();
#endif
  }

  int side = Wire.read();
  int dir = Wire.read();
  int pwm = Wire.read();

#ifdef SERIAL_OUTPUT
  Serial.print("Side: ");
  Serial.print(side);
  Serial.print(" Direction: ");
  Serial.print(dir);
  Serial.print(" PWM-Value: ");
  Serial.println(pwm);
#endif
  // Update motor values

  if (side == MOTOR_BOTH) {
    if (dir == MOTOR_FORWARD) {
      motorLeft.vor(pwm);
      motorRight.vor(pwm);
    } else if (dir == MOTOR_BACKWARD) {
      motorLeft.zurueck(pwm);
      motorRight.zurueck(pwm);
    } else if (dir == MOTOR_OFF) {
      motorLeft.aus();
      motorRight.aus();
    }
  } else if (side == MOTOR_LEFT) {
    if (dir == MOTOR_FORWARD)
      motorLeft.vor(pwm);

    else if (dir == MOTOR_BACKWARD)
      motorLeft.zurueck(pwm);

    else if (dir == MOTOR_OFF)
      motorLeft.aus();

  } else if (side == MOTOR_RIGHT) {
    if (dir == MOTOR_FORWARD)
      motorRight.vor(pwm);

    else if (dir == MOTOR_BACKWARD)
      motorRight.zurueck(pwm);

    else if (dir == MOTOR_OFF)
      motorRight.aus();

  }

  digitalWrite(LED_BUILTIN, LOW);
}
