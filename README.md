# WeatherCollector
This is the repository for Paul and Ezhar's Engineering III Weather Data Collection project

## Table of Contents
* [Overview](#overview)
* [Design](#design)
* [Code Prototypes](#code-prototypes)
* [Final Arduino Code](#final-arduino-code)
* [Web Dashboard](#web-dashboard)
* [CAD](#cad)
* [Assembly](#assembly)
* [Final Results](#final-results)

<br>
<br>

## Additional Documentation
* [Plan](docs/plan.md)
* [Research](docs/research.md)

<br>
<br>

## Overview

The first project of Engineering III was to create a **robot arm**. However, as the Engineering program was working on a project to bring a wind turbine onto the school grounds, we (Ezhar Zahid and Paul Schakel) were recruited to gather data on the weather at the school. After much planning and deliberation, we settled on a design that would gather data on *Temperature, Humidity, Pressure, and Wind Speed*. This data would then be sent to the cloud and be displayed on a public dashboard. For more details on the initial design, see our [plan](docs/plan.md).

<br>

## Tools Used
- CAD - [Onshape](https://www.onshape.com/en/)

- Code - [VS Code](https://code.visualstudio.com/)

- Wiring Diagram - [Fritzing](https://fritzing.org/)

- Arduino Communication - [Arduino IoT Cloud](https://docs.arduino.cc/cloud/iot-cloud)

- Webhooks Integration - [IFTTT](https://ifttt.com/)

- Web Hosting - [Python Anywhere](https://pythonanywhere.com)

<br>
<br>

## Design

In the design for our enclosure, we had to take several factors into account: space for sensors, air access, and most importantly **Weather Proofing**. The latter two were somewhat in conflict, so we had to figure out how to let the sensors have access to outside air, while still being waterproof. Our initial idea was to have a circular box with several layers with gaps underneath, but this proved to be too inefficient with the material, and it was scrapped. 

<img src="images/initial_sketch_design.jpg" height=300px>

Initial design for door on top - scrapped soon afterward as we needed to put the wind guage on top. Note that the design is ambuguous as to what shape the enclosure would be.

<br>
<br>

## Code Prototypes

Before getting very far, we had to create prototypes of the sensors and various components of the project as a proof of concept. Upon completion, several of the prototypes were brought into the [final code](#final-code) for the Arduino, following some modification.

### List of Prototypes
* [MKR Carrier](prototypes/MKR_Carrier/MKR_Carrier.ino) - prototype of OLED screen and capacative touch buttons
* [Humidity and Temperature](prototypes/humidity_temp/humidity_temp.ino) - prototype of Humidity and Temperature sensors on MKR Carrier
* [Pressure and Temperature](prototypes/pressure_temp/pressure_temp.ino) - prototype of Pressure and Temperature sensors - not used in final design
* [WiFi Connection](prototypes/wifi_connection/wifi_connection.ino) - prototype of WiFi connection on Arduino MKR 1010 - used different method in final design
* [Wind Speed](prototypes/wind_speed/wind_speed.ino) - prototype of Wind Speed sensor (Anemometer)

Some of the prototypes weren't used in the final design, such as the prototype of the Pressure and Temperature sensor, which was scrapped because we discovered later on that the MKR Carrier has a pressure sensor, and adding another component didn't really make sense. Most of the prototypes were smooth sailing, just a simple job of looking up an example and testing it out. However, we did have some trouble with the Wind Speed sensor. 

The Wind Speed sensor is supposed to output a voltage between 0.4V and 2V, but when we initially tested it, all we could read was random voltages that had no bearing on wind speed. After messing with the wiring for a while, we realized that it wasn't sharing a ground connection with the Arduino. After connecting the Wind Speed sensor to ground, it worked perfectly.

<br>
<br>

## Final Arduino Code



## Web Dashboard



## CAD
