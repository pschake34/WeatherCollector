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
  int uptime;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

#include "thingProperties.h"
#include <Arduino_MKRIoTCarrier.h>
#include <Adafruit_MPL3115A2.h>
#include <Wire.h>

//Adafruit_MPL3115A2 myPressure;
MKRIoTCarrier carrier;

float tempC1 = 0;
float tempC2 = 0;
float pressurekPa = 0;

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  while(!Serial){}
  Serial.println("Started Serial...");

  //Set if it has the Enclosure mounted
  CARRIER_CASE = false;
  //Initialize the IoTSK carrier and output any errors in the serial monitor
  carrier.begin();
  Serial.println("Carrier has begun");

  //Wire.begin();        // Join i2c bus
  //myPressure.begin();  // Initialize pressure sensor 


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
  Serial.println("Print information");
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  Serial.println("Made it past this point 1");
  
  //Wait to get cloud connection to init the carrier
  while (ArduinoCloud.connected() != 1) {
    Serial.println("Made it past this point 2");
    ArduinoCloud.update();
    Serial.println("Not Connected");
    delay(500);
  }
  delay(500);
}

void loop() {
  ArduinoCloud.update();
  
  tempC1 = carrier.Env.readTemperature();
  //tempC2 = myPressure.getTemperature();
  humidity = carrier.Env.readHumidity();
  pressurekPa = carrier.Pressure.readPressure();
  pressure = pressurekPa * 0.2953;
  
  
  temperature = (tempC1 * 9/5) + 32 - 7;   //convert to Fahrenheit
  
  Serial.println("Temperature (C): " + (String) tempC1);
  //Serial.println("Temperature (C): " + (String) tempC2);
  Serial.println("Temperature (F): " + (String) temperature);
  Serial.println("Humidity: " + (String) humidity + "%");
  Serial.println("Pressure (inHg): " + (String) pressure);

  delay(500);
}

