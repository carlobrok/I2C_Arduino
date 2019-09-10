#include <Wire.h>

#define SLAVE_ADDRESS 0x08
#define SERIAL_OUTPUT

#define ALL_SENSOR_VALUES 1
#define DIGITAL_SENSOR_VALUES 2
#define ANALOG_SENSOR_VALUES 3


int command = 0;

void setup() {
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  
  pinMode(LED_BUILTIN, OUTPUT);

#ifdef SERIAL_OUTPUT
  Serial.begin(115200);
#endif
}



void loop() {
}


void receiveEvent(int byte_amount) {

#ifdef SERIAL_OUTPUT
  Serial.print("Anzahl: ");
  Serial.print(byte_amount);
#endif

  digitalWrite(LED_BUILTIN, HIGH);

  command = Wire.read();
#ifdef SERIAL_OUTPUT
  Serial.print(command);
  
  if(command == ALL_SENSOR_VALUES) {
    Serial.print(" write all sensor values");
  } else if(command == DIGITAL_SENSOR_VALUES) {
    Serial.print(" write all sensor values");
  } else if(command == ANALOG_SENSOR_VALUES) {
    Serial.print(" write all sensor values");
  }
  Serial.println();
#endif
  
  digitalWrite(LED_BUILTIN, LOW);
}


void requestEvent() {
  if(command == ALL_SENSOR_VALUES) {
    Wire.write(5); // respond with message of 6 bytes
    Wire.write(5); // respond with message of 6 bytes
    Wire.write(5); // respond with message of 6 bytes
    Wire.write(5); // respond with message of 6 bytes
    Wire.write(5); // respond with message of 6 bytes
    Wire.write(5); // respond with message of 6 bytes
  } else if(command == DIGITAL_SENSOR_VALUES) {
    Serial.print(" write all sensor values");
  } else if(command == ANALOG_SENSOR_VALUES) {
    Serial.print(" write all sensor values");
  }
}
