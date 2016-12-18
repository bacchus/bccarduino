#include <Wire.h>
#include <Adafruit_BMP085.h>

// VCC - 3.3V
// GND - GND
// SCL - A5
// SDA - A4
 
Adafruit_BMP085 bmp;
 
void setup() 
{
  Serial.begin(9600);
  if (!bmp.begin()) 
  {
  Serial.println("BMP180 sensor not found");
  while (1) {}
  }
}
 
void loop() {
    float presPa = bmp.readPressure();
    int presHg = presPa/133.322f;
    
    Serial.print("Pressure = ");
    Serial.print(presHg);
    Serial.println(" mmHg");
    
    Serial.print("Temperature = ");
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");
 
    Serial.print("Altitude = ");
    Serial.print(bmp.readAltitude());
    Serial.println(" m");
 
    Serial.println();
    delay(5000);
}

