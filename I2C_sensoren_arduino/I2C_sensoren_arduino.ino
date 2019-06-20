
#include <Wire.h>
#define SLAVE_ADRESS 0x08


byte response[2]; // this data is sent to PI
volatile short LDR_value; // Global Declaration
const int LDR_pin=A0; //pin to which LDR is connected A0 is analog 

void setup() {
  
  Wire.begin(SLAVE_ADDRESS); // this will begin I2C Connection with 0x40 address
  Wire.onRequest(sendData); // sendData is funtion called when Pi requests data
  pinMode(LDR_pin,INPUT);

}

void loop() 
{
  LDR_value= 500 ;
  // Arduino returns 10bit data but we need to convert it to 8bit 
  LDR_value=map(LDR_value,0,1023,0,255);
  response[0]=(byte)LDR_value;
  Wire.write(response,2); // return data to PI

  
  delay(1000);
}

byte data = 0;

/*void sendData()
{
}*/
