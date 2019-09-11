#include <Wire.h>

#define SLAVE_ADDRESS 0x09

#define DEBUG_COM
#define DEBUG_SEN_DATA

#define ALL_SENSOR_VALUES 1
#define DIGITAL_SENSOR_VALUES 2
#define ANALOG_SENSOR_VALUES 3

// Definition: <Sensortyp>_<Ausrichtung>_<Seite>[_Entfernung/Größe/Kennzeichnung]

// DIGITAL ======

#define DIGITAL_SEN_AMOUNT 8

#define IR_VORNE_L 4
#define IR_VORNE_R 5

#define IR_LINKS_V 6
#define IR_LINKS_H 7

#define IR_RECHTS_V 8
#define IR_RECHTS_H 9

#define T_HINTEN_L 10
#define T_HINTEN_R 11

// ANALOG =======

#define ANALOG_SEN_AMOUNT 1

#define IR_VORNE_M A0

// END DEF =====


int digital_sensors[DIGITAL_SEN_AMOUNT] = {IR_VORNE_L, IR_VORNE_R, IR_LINKS_V, IR_LINKS_H, IR_RECHTS_V, IR_RECHTS_H, T_HINTEN_L, T_HINTEN_R};
bool digital_sensor_data[DIGITAL_SEN_AMOUNT];    // All bits of digital sensors

#ifdef DEBUG_SEN_DATA
String digital_sensors_str[DIGITAL_SEN_AMOUNT] = {"IR_VORNE_L", "IR_VORNE_R", "IR_LINKS_V", "IR_LINKS_H", "IR_RECHTS_V", "IR_RECHTS_H", "T_HINTEN_L", "T_HINTEN_R"};
#endif

// analog_sensors is an array because maybe there will be some more sensors.
int analog_sensors[1] = {IR_VORNE_M};
int analog_sensor_data[1];      // All bytes of analog sensors





int command = 0;

void setup() {
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  
  pinMode(LED_BUILTIN, OUTPUT);

#if defined(DEBUG_COM) || defined(DEBUG_SEN_DATA)
  Serial.begin(115200);
  Serial.println("Running sensor program...");
#endif
}



void loop() {
  for (int i = 0; i < DIGITAL_SEN_AMOUNT; i++) {
    digital_sensor_data[i] = digitalRead(digital_sensors[i]);
  }
  for (int i = 0; i < ANALOG_SEN_AMOUNT; i++) {
    analog_sensor_data[i] = analogRead(analog_sensors[i]);
  }

#ifdef DEBUG_SEN_DATA
  for(int i = 0; i < DIGITAL_SEN_AMOUNT; i++) {
    Serial.print(digital_sensors_str[i]);
    Serial.print(" ");
    Serial.print(digital_sensor_data[i]);
    Serial.print(" ");
  }
  Serial.println("");
#endif
}


void receiveEvent(int byte_amount) {

#ifdef DEBUG_COM
  Serial.print("Anzahl: ");
  Serial.print(byte_amount);
#endif

  digitalWrite(LED_BUILTIN, HIGH);

  command = Wire.read();

#ifdef DEBUG_COM
  Serial.print("; ");
  Serial.print(command);
  if(command == ALL_SENSOR_VALUES) {
    Serial.print(" > write all sensor values");
  } else if(command == DIGITAL_SENSOR_VALUES) {
    Serial.print(" > write only digital sensor values");
  } else if(command == ANALOG_SENSOR_VALUES) {
    Serial.print(" > write only analog sensor values");
  }
  Serial.println();
#endif
  
  digitalWrite(LED_BUILTIN, LOW);
}


void requestEvent() {
  if(command == ALL_SENSOR_VALUES) {
    byte compressed_data_digital = digital_sensor_data[0];
    for (int i = 1; i < 8; i++) {
      compressed_data_digital = (compressed_data_digital << 1) | digital_sensor_data[i];
    }
    
    Wire.write(compressed_data_digital); // return data to PI 
 #ifdef DEBUG_COM
    Serial.println("Send data.");
 #endif
  } else if(command == DIGITAL_SENSOR_VALUES) {
    
    
    
  } else if(command == ANALOG_SENSOR_VALUES) {


    
  }
  command = 0;
}
