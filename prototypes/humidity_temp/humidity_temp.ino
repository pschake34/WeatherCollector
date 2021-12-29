// Paul Schakel
// humidity_temp.ino
// Prototype for measuring pressure and temperature using the MKR IoT Carrier

#include <Arduino_MKRIoTCarrier.h>

MKRIoTCarrier carrier;

float tempC = 0;
float humidity = 0;

void setup() {
    Serial.begin(115200);

    while(!Serial){}
    Serial.println("Started Serial...");

    //Set if it has the Enclosure mounted
    CARRIER_CASE = false;
    //Initialize the IoTSK carrier and output any errors in the serial monitor
    carrier.begin();
}

void loop() {
    tempC = carrier.Env.readTemperature();
    humidity = carrier.Env.readHumidity();
    float tempF = (tempC * 9/5) + 32;   //convert to Fahrenheit

    Serial.println("Temperature (C): " + (String) tempC);
    Serial.println("Temperature (F): " + (String) tempF);
    Serial.println("Humidity: " + (String) humidity + "%");
}