# Research

This has links to research we've done on various components of the weather station project

## Table of Contents

* [Programming the Sensors](#programming-the-sensors)
* [Arduino wireless communication](#arduino-wireless-communication)

<br>
<br>

## Programming the sensors

Sensor | What it measures | Protocol | Research Link
--- | --- | --- | ---
Thermometer/Hygrometer | Temperature and humidity | Easy Arduino library - integrated into IoT starter kit | [temp and humidity sensor](https://explore-iot.arduino.cc/iotsk/module/iot-starter-kit/lesson/get-to-know-the-kit)
Anemometer | Wind speed | Voltage output between 0.4 and 2 volts | [anemometer](https://how2electronics.com/measure-wind-speed-using-anemometer-arduino/)
Barometer/Thermometer | Pressure and Temperature | I2C | [barometer/thermometer](https://learn.adafruit.com/using-mpl3115a2-with-circuitpython?view=all)
Rainwater detection | How fast rainwater falls | Voltage pulse | found by trial and error

## Arduino Wireless communication

The wireless communication from the Arduino will be accomplished via [Arduino IoT Cloud](https://docs.arduino.cc/cloud/iot-cloud/tutorials/iot-cloud-getting-started), the data from which will be processed through webhooks to the public web server. The public web server will be a small [flask](https://flask.palletsprojects.com/en/2.0.x/) app with a dashboard to view weather data from the present and past.
