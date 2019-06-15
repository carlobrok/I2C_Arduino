#define SERIAL_OUTPUT
#include <Wire.h>
//#include "KamelMotor.h"

void setup() {
  Wire.begin(0x08);
  Wire.onReceive(receiveEvent);

#ifdef SERIAL_OUTPUT
  Serial.begin(115200);
#endif
}

void loop() {

  // Motoren ansteuern

  //delay(100);
}

void receiveEvent(int byte_amount) {
  /*if (byte_amount != 2) {
#ifdef SERIAL_OUTPUT
    Serial.print("Wrong byte amount! ");
    Serial.println(byte_amount);
#endif
  } else {
*/
    Serial.print("Anzahl: ");
    Serial.println(byte_amount);
    while (Wire.available()) { // loop through all but the last
      int c = Wire.read(); // receive byte as a character
      Serial.print(c);         // print the character
      Serial.print(" ");
    }
    Serial.println();
    
    // Update motor values

  //}
}
