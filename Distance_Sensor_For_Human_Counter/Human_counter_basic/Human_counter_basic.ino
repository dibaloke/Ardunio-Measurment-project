#include <Wire.h>
#include <VL53L0X.h>

int a=0,b=0,count=0,d=500;
 
 
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
  a=Sensor1.readRangeContinuousMillimeters();
  Serial.print(a);
  Serial.print(",    ");
  b=Sensor2.readRangeContinuousMillimeters();
 Serial.print(b);
 Serial.print(",    ");
 
  //Serial.println();

  if (a<d)
  {
    while(1)
    {
      Serial.println("in 1 inf");
      
      a=Sensor1.readRangeContinuousMillimeters();
      b=Sensor2.readRangeContinuousMillimeters();
      if(b<d)
      {
        while(1)
        {
          Serial.println("in 2 inf");
          a=Sensor1.readRangeContinuousMillimeters();
          b=Sensor2.readRangeContinuousMillimeters();
          if(b>d)
          {
            break;
          }
        
        }
       
        count++;
        break;
      }
      
    }
  }




  else if (b<d)
  {
    while(1)
    {
      Serial.println("out 1 inf");
       
      a=Sensor1.readRangeContinuousMillimeters();
      b=Sensor2.readRangeContinuousMillimeters();
      if(a<d)
      {
        
        while(1)
        {
          Serial.println("out 2 inf");
          a=Sensor1.readRangeContinuousMillimeters();
          b=Sensor2.readRangeContinuousMillimeters();
          if(a>d)
          {
            break;
          }
        
        }
       
        count--;
        break;
      }
      
    }
  }

  
Serial.println(count);
  
}
