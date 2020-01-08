#include <Wire.h>
#include "Motor.h"

#define SERIAL_OUTPUT
#define SLAVE_ADDRESS 0x08

Motor motorRight(5, 7, 8, A0, 2);
Motor motorLeft(6, 9, 10, A1, 3);

template<class T>
void print(T message) {
#ifdef SERIAL_OUTPUT
  Serial.print(message);
#endif
}

template<class T>
void println(T message) {
#ifdef SERIAL_OUTPUT
  Serial.println(message);
#endif
}


void setup() {
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveEvent);

  pinMode(LED_BUILTIN, OUTPUT);

#ifdef SERIAL_OUTPUT
  Serial.begin(115200);
#endif

  println("Motoren Arduino");
  print("Adresse: "); Serial.println(SLAVE_ADDRESS);

}

inline void recieveError() {
  println("WARNING: Recieved wrong/corrupted data");
}


void loop() {

  // Motoren ansteuern

  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(3000 - 100);
}

void receiveEvent(int byte_amount) {


  print("Anzahl: ");
  println(byte_amount);


  if (byte_amount == 2) {
    recieveError();
    return;
  }

  digitalWrite(LED_BUILTIN, HIGH);

  int command = Wire.read();
  int puffer_b = Wire.read();

  print("Comand: ");
  print(command);
  print("\tBuffer: ");
  print(puffer_b);

  int inbytes[byte_amount - 2];

  int index = 0;
  print("  data: [");
  while (Wire.available()/* && index < byte_amount - 2*/) {
    inbytes[index++] = Wire.read();
    print(inbytes[index - 1]);
    if(Wire.available() > 0)
      print(";");
  }
  println("]");


  if (command == MOTOR_DIR_PWM) {
    int side = inbytes[0];
    int dir = inbytes[1];
    int pwm = inbytes[2];

    println("MOTOR_DIR_PWM");

    if (side == MOTOR_LEFT) {
      motorLeft.update(dir, pwm);
    } else if (side == MOTOR_RIGHT) {
      motorRight.update(dir, pwm);
    } else if (side == MOTOR_BOTH) {
      motorLeft.update(dir, pwm);
      motorRight.update(dir, pwm);
    }
  } else if (command == MOTOR_DIR_PWM_BOTH) {
    int dir_l = inbytes[0];
    int pwm_l = inbytes[1];
    int dir_r = inbytes[2];
    int pwm_r = inbytes[3];

    println("MOTOR_DIR_PWM_BOTH");

    motorLeft.update(dir_l, pwm_l);
    motorRight.update(dir_r, pwm_r);

  } else if (command = MOTOR_STATE) {
    int side = inbytes[0];
    int state = inbytes[1];

    println("MOTOR_STATE");

    if (side == MOTOR_LEFT) {
      motorLeft.update(state);
    } else if (side == MOTOR_RIGHT) {
      motorRight.update(state);
    } else if (side == MOTOR_BOTH) {
      motorLeft.update(state);
      motorRight.update(state);
    } else {
      recieveError();
    }
  } else {
    recieveError();
  }

  digitalWrite(LED_BUILTIN, LOW);
}
