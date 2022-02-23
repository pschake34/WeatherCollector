/* 
  Paul Schakel, Jan 2022
  
  Sketch generated for the Arduino IoT Cloud Thing "Weather Station"
  https://create.arduino.cc/cloud/things/bd8cbadf-21f5-4406-aecb-1a12cf544365 

  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  float humidity;
  float pressure;
  float temperature;
  float windSpeed;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

#include "thingProperties.h"
#include <Arduino_MKRIoTCarrier.h>
#include <Wire.h>

MKRIoTCarrier carrier;

float tempC1 = 0;
float tempC2 = 0;
float pressurekPa = 0;

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  while(!Serial){}
  Serial.println(F("Started Serial..."));

  //Set if it has the Enclosure mounted
  CARRIER_CASE = false;
  //Initialize the IoTSK carrier and output any errors in the serial monitor
  carrier.begin();
  Serial.println(F("Carrier has begun"));

  carrier.display.fillScreen(ST7735_BLACK);
  carrier.display.setTextColor(ST7735_WHITE);
  carrier.display.setTextSize(3.5);
  carrier.display.setCursor(0, 120);
  carrier.display.println("Connecting...");

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  Serial.println(F("Print information: "));
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  
  //Wait to get cloud connection to init the carrier
  while (ArduinoCloud.connected() != 1) {
    ArduinoCloud.update();
    Serial.println(F("Waiting..."));
    delay(500);
  }
  delay(500);

  carrier.display.fillScreen(ST7735_BLACK);
}

void loop() {
  ArduinoCloud.update();
  
  tempC1 = carrier.Env.readTemperature();
  humidity = carrier.Env.readHumidity();
  pressurekPa = carrier.Pressure.readPressure();
  pressure = pressurekPa * 0.2953;
  
  temperature = (tempC1 * 9/5) + 32 - 7;   //convert to Fahrenheit
  
  Serial.println("Temperature (C): " + (String) tempC1);
  Serial.println("Temperature (F): " + (String) temperature);
  Serial.println("Humidity: " + (String) humidity + "%");
  Serial.println("Pressure (inHg): " + (String) pressure);

  carrier.display.fillScreen(ST7735_BLACK);
  carrier.display.setCursor(0, 0);
  carrier.display.println("Temp: " + (String) temperature + "F");
  carrier.display.println("\nHmdty: " + (String) humidity + "%");
  carrier.display.println("\nPrs: " + (String) pressure + "inHg");

  delay(2000);
}

