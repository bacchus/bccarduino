#include <DHT.h>

//#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#define DHT_PIN A0
#define DHT_TYPE DHT11

Adafruit_PCD8544 display = Adafruit_PCD8544(3, 4, 5, 6, 7);

DHT dht_sens(DHT_PIN, DHT_TYPE);

void setup() {

  //Serial.begin(9600);
    
  display.begin();
  display.clearDisplay();
  display.display();
  display.setContrast(50);
  display.setRotation(2);

  display.setCursor(0, 0);
  display.setTextColor(BLACK);
  display.setTextSize(1);
  display.print("Hello kittie!");
  display.display();

  dht_sens.begin();

  delay(1000);
}

void loop() {
  delay(10000);

  float hum = dht_sens.readHumidity();
  float tep = dht_sens.readTemperature();

  display.clearDisplay();
  display.display();
  delay(1000);

//  display.print("time: ");
//  long tm = millis();
//  tm /= 1000;
//  display.print(tm);

  if (isnan(hum) || isnan(tep)) {
    display.setCursor(0, 10);
    display.print("Fail DHT");
    //Serial.print("Fail DHT\n");
    
  } else {
//    Serial.print("hum: ");
//    Serial.print(hum);
//    Serial.print(" %");
//
//    Serial.print("    tep: ");
//    Serial.print(tep);
//    Serial.print(" *C");
    
    display.setCursor(0, 10);
    display.print("H:");
    display.print(hum);
    display.print(" %");

    display.setCursor(0, 20);
    display.print("T:");
    display.print(tep);
    display.print(" *C");
  }

  display.display();
  //Serial.print("\n");
}

