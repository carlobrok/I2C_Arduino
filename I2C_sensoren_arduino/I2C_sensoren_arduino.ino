#include <Wire.h>

#define SLAVE_ADDRESS 0x08

#define SERIAL_OUTPUT

void setup() {
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveEvent);

  pinMode(LED_BUILTIN, OUTPUT);

#ifdef SERIAL_OUTPUT
  Serial.begin(115200);
#endif
}



void loop() {
  // put your main code here, to run repeatedly:

}


void receiveEvent(int byte_amount) {

#ifdef SERIAL_OUTPUT
  Serial.print("Anzahl: ");
  Serial.println(byte_amount);
#endif

  digitalWrite(LED_BUILTIN, HIGH);

  int command = Wire.read();
  
  if(command == 1) {
    Serial.println("1");
  }
  


  digitalWrite(LED_BUILTIN, LOW);
}
