
#include <Wire.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 mySensor; // create an object

float tempc;
float tempf;
float pressure;

void setup() { 
  Serial.begin(9600);
  mySensor.begin(); // initialise mySensor
}

void loop() {
  tempc = mySensor.readTemperature(); // read the temperature in celsius
  tempf = tempc * 1.8 + 32; 
  pressure = mySensor.readPressure(); // read the pressure

  Serial.print("The temp is: ");
  Serial.print(tempf);
  Serial.println(" degrees F");
  Serial.print("The pressure is ");
  Serial.print(pressure/3386.389); // pressure in pascals
  Serial.println(" in HG");
  Serial.println("");
  delay(250);
}
