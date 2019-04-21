#include <Wire.h>
#include <VL53L0X.h>


#define XSHUT_pin1 10


#define Sensor2_newAddress 42


VL53L0X Sensor1;
VL53L0X Sensor2;

void setup()
{ 
  pinMode(XSHUT_pin1, OUTPUT);

  
  Serial.begin(9600);
  
  Wire.begin();

  Sensor2.setAddress(Sensor2_newAddress);
  pinMode(XSHUT_pin1, INPUT);
  delay(10);
  
  Sensor1.init();
  Sensor2.init();

  
  Sensor1.setTimeout(500);
  Sensor2.setTimeout(500);


  
  Sensor1.startContinuous();
  Sensor2.startContinuous();


}

void loop()
{
  Serial.print(Sensor1.readRangeContinuousMillimeters());
  Serial.print(',');
  Serial.print(Sensor2.readRangeContinuousMillimeters());
  Serial.print(',');

  Serial.println();
}