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
File dataFile

float tempC1 = 0;
float tempC2 = 0;
float pressurekPa = 0;

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(5000);
  Serial.println(F("Started Serial..."));

  //Set if it has the Enclosure mounted
  CARRIER_CASE = false;
  //Initialize the IoTSK carrier and output any errors in the serial monitor
  carrier.begin();
  Serial.println(F("Carrier has begun"));
  	
  // init SD card
  if (!SD.begin(SD_CS)) {
    carrier.display.setTextSize(2);
    carrier.display.setCursor(35, 70);
    carrier.display.print("SD card failed");
    carrier.display.setCursor(45, 110);
    carrier.display.print("to initialise");
    while (1);
  }

  //init the logfile
  dataFile = SD.open("log-0000.csv", FILE_WRITE);
  delay(1000);

  dataFile.println("temperature,humidity,pressure,windSpeed")
  dataFile.close();
  delay(100);

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

  // init the logfile
  dataFile = SD.open("log-0000.csv", FILE_WRITE);
  delay(1000);

  //get wind speed
  float sensorValue = analogRead(A1);
  float voltage = (sensorValue / 960) * 5;
  Serial.println(voltage);
  float windSpeedMs = mapfloat(voltage, 0.62, 1.7, 0, 32.4);
  windSpeed = ((windSpeedMs *3600)/1609.344) - 2; //convert from meters per hour to miles
  if (windSpeed < 0) {
    windSpeed = 0;
  }

  tempC1 = carrier.Env.readTemperature();
  humidity = carrier.Env.readHumidity();
  pressurekPa = carrier.Pressure.readPressure();
  pressure = pressurekPa * 0.2953;
  
  temperature = (tempC1 * 9/5) + 32 - 7;   //convert to Fahrenheit
  
  //print to serial monitor
  Serial.println("Temperature (C): " + (String) tempC1);
  Serial.println("Temperature (F): " + (String) temperature);
  Serial.println("Humidity: " + (String) humidity + "%");
  Serial.println("Pressure (inHg): " + (String) pressure);
  Serial.println("Wind Speed (Mph): " + (String) windSpeed);

  //display on screen
  carrier.display.fillScreen(ST7735_BLACK);
  carrier.display.setCursor(0, 0);
  carrier.display.println("Temp: " + (String) temperature + "F");
  carrier.display.println("\nHmdty: " + (String) humidity + "%");
  carrier.display.println("\nPrs: " + (String) pressure + "inHg");
  carrier.display.println("\nWS: " + (String) windSpeed + "Mph");

  //write to logfile
  dataFile.print("" + (String) temperature + ",");
  dataFile.print("" + (String) humidity + ",");
  dataFile.print("" + (String) pressure + ",");
  dataFile.println("" + (String) windSpeed + ",");
  dataFile.close();

  Serial.println("Logging successful...");

  delay(2000);
}

// Utility funcion for getting wind speed
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
