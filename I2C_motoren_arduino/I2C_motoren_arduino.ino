#include <Wire.h>
#include "Motor.h"

#define SERIAL_OUTPUT

Motor motorRight(5, 7, 8, A0, 2);
Motor motorLeft(6, 9, 10, A1, 3);

void setup() {
  Wire.begin(0x08);
  Wire.onReceive(receiveEvent);

  pinMode(LED_BUILTIN, OUTPUT);

#ifdef SERIAL_OUTPUT
  Serial.begin(115200);
#endif
}

inline void recieveError() {
#ifdef SERIAL_OUTPUT
  Serial.println("WARNING: Recieved wrong/corrupted data");
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

#ifdef SERIAL_OUTPUT
  Serial.print("Anzahl: ");
  Serial.println(byte_amount);
#endif

  if (byte_amount == 2) {
    recieveError();
    return;
  }

  digitalWrite(LED_BUILTIN, HIGH);

  int command = Wire.read();
  int puffer_b = Wire.read();

  Serial.print("Comand: ");
  Serial.print(command);
  Serial.print("\tPuffer: ");
  Serial.println(puffer_b);

  int inbytes[byte_amount - 2];

  int index = 0;
  while (Wire.available() && index < byte_amount - 2) {
    inbytes[index++] = Wire.read();
    Serial.print(inbytes[index - 1]);
    Serial.print(" ");
  }
  Serial.println();


  if (command == MOTOR_DIR_PWM) {
    int side = inbytes[0];
    int dir = inbytes[1];
    int pwm = inbytes[2];

    if (side == MOTOR_LEFT) {
      motorLeft.update(dir, pwm);
    } else if (side == MOTOR_RIGHT) {
      motorRight.update(dir, pwm);
    } else if (side == MOTOR_BOTH) {
      motorLeft.update(dir, pwm);
      motorRight.update(dir, pwm);
    }
  }
  else if (command == MOTOR_DIR_PWM_BOTH) {
    int dir_l = inbytes[0];
    int pwm_l = inbytes[1];
    int dir_r = inbytes[2];
    int pwm_r = inbytes[3];

    motorLeft.update(dir_l, pwm_l);
    motorRight.update(dir_r, pwm_r);

  } else if (command = MOTOR_STATE) {
    int side = inbytes[0];
    int state = inbytes[1];

    if (side == MOTOR_LEFT) {
      motorLeft.update(state);
    } else if (side == MOTOR_RIGHT) {
      motorRight.update(state);
    } else if (side == MOTOR_BOTH) {
      motorLeft.update(state);
      motorRight.update(dir, pwm);
    } else [
      recieveError();
    }
  } else {
    recieveError();
  }

  digitalWrite(LED_BUILTIN, LOW);
}
