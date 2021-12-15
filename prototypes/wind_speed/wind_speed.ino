// Paul Schakel & Ezhar Zahid
// Wind Speed
// Prototype testing out an Adafruit wind sensor 

void setup() {
    Serial.begin(9600);
    Serial.println("Initialized...");
}

void loop() {
    float sensorValue = analogRead(A1);
    Serial.print("Analog Value =");
    Serial.println(sensorValue);
    delay(500);

    float voltage = (sensorValue / 960) * 5;
    Serial.print("Voltage: ");
    Serial.print(voltage);
    Serial.println("V");

    float wind_speed = mapfloat(voltage, 0.4, 2, 0, 32.4);
    float speed_mph = ((wind_speed *3600)/1609.344); //convert from meters per hour to miles
    Serial.print("Wind Speed =");
    Serial.print(wind_speed);
    Serial.println("m/s");
    Serial.print(speed_mph);
    Serial.println("mph");
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}