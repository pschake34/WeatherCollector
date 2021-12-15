// Paul Schakel

#include <Adafruit_MPL3115A2.h>
#include <Wire.h>

Adafruit_MPL3115A2 myPressure;

void setup() {
    Serial.begin(9600);
    Serial.println("Initialized...");
    
    Wire.begin();        // Join i2c bus
    myPressure.begin();
}

void loop() {
    float pressure = myPressure.getPressure();
    float tempC = myPressure.getTemperature();
    float tempF = (tempC * 9/5) + 32;

    Serial.println("Pressure (Pascals): " + (String) pressure);
    Serial.println("Temperature (C): " + (String) tempC);
    Serial.println("Temperature (F): " + (String) tempF);
    delay(5000);
}