#include <Wire.h>
#define SLAVE_ADDRESS 0x09

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

// analog_sensors is an array because maybe there will be some more sensors.
int analog_sensors[1] = {IR_VORNE_M};
int analog_sensor_data[1];      // All bytes of analog sensors


// Debug variables

#define LED_ON_TIME 20    // Time led will be on when data is send
#define LED_ON_TIME_STANDBY 100
bool led_on = false;
bool led_standby_mode;
unsigned long led_last_change = 0;
unsigned long led_last_change_standby = 0;

inline void led_debug() {
  led_last_change = millis();
  led_on = true;
}

inline void set_led() {
  if(millis() - led_last_change >= LED_ON_TIME && led_on) {
    led_on = false;
  }
  if(millis() - led_last_change >= 2000 && millis() - led_last_change_standby >= LED_ON_TIME_STANDBY) {
    led_on = !led_on;
    led_last_change_standby = millis();
  } 
  digitalWrite(LED_BUILTIN, led_on);
}

void setup() {
  Wire.begin(SLAVE_ADDRESS); // begin I2C Connection with 0x09 address

  for(int i = 0; i < DIGITAL_SEN_AMOUNT; i++) {
    digital_sensor_data[i] = 0;
  }
  for(int i = 0; i < ANALOG_SEN_AMOUNT; i++) {
    analog_sensor_data[i] = 0;
  }
  
  Wire.onRequest(sendData); // sendData is called when Pi requests data 
  pinMode(LED_BUILTIN, OUTPUT);   // Debug LED
}


void sendData() {

  // CHANGE FOLLOWING CODE IF MORE THAN 8 DIGITAL SENSORS CONNECTED!!!
  
  byte compressed_data_digital = digital_sensor_data[0];
  for(int i = 1; i < 8; i++) {
    compressed_data_digital = compressed_data_digital << 1;
    compressed_data_digital += digital_sensor_data[i];
  }
  
  Wire.write(compressed_data_digital); // return data to PI
  led_debug();
}


void loop() 
{
  for(int i = 0; i < DIGITAL_SEN_AMOUNT; i++) {
    digital_sensor_data[i] = digitalRead(digital_sensors[i]);
  }
  for(int i = 0; i < ANALOG_SEN_AMOUNT; i++) {
    analog_sensor_data[i] = analogRead(analog_sensors[i]);
  }
  set_led();
}
