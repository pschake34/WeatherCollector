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

In the design for our enclosure, we had to take several factors into account: space for sensors, air access, and most importantly **Weather Proofing**. The latter two were somewhat in conflict, so we had to figure out how to let the sensors have access to outside air, while still being waterproof. Our initial idea was to have a circular box with several layers with gaps underneath (similar to image below), but this proved to be too inefficient with the material, and it was scrapped. The design we eventually went with used an overhanging roof with small air slots just beneath it.

<img src="images/enclosure.jpeg" height=300px><img src="images/initial_sketch_design.jpg" height=300px>

Left - Initial idea for weatherproofing

Right - Initial design for door on top - scrapped soon afterward as we needed to put the wind guage on top. Note that the design is ambuguous as to what shape the enclosure would be.

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

Creating the final version of the code seemed like a simple task at first - simply slapping all the prototypes into one file and calling it a day. However, some unforseen difficulties with the wifi connection prototype required a whole new solution, and additional features, such as storing the data on an SD card, were needed. Unfortunately, these additional tasks led to some small setbacks in terms of timelyness.

### Arduino IoT Cloud

The solution to our internet communication problem turned out to be using the official method [hosted by Arduino](https://docs.arduino.cc/cloud/iot-cloud). In a very short time, we were able to get our Arduino sending data to the cloud and see a live dashboard with the most recent data. However, it did have some issues that will be addressed later.

[Link To Final Arduino Code](/arduino_code/WeatherStation.ino)

### Sensors

There weren't any major issues with the sensors, as it was just pasting from the prototypes, but there had to be some changes made in terms of which sensors were used. Our original idea was to use the sensors from the IoT Shield as well as an external sensor for temperature and pressure. However, the I2C connection from the external sensor into the Arduino MKR 1010 made the WiFi module unable to connect. Luckily, the IoT Shield had a barometric pressure module that we had previously overlooked, and a crisis was averted.

### Reflection

TODO: Actionable Information

## Web Dashboard



## CAD



### Discription

The **weather box** is designed to keep everything *weather proof* and safe from outside interference. the base is **4.88 inches x4.88 inches**. It has a battery pack cutout **(63.70mm x 94.40 mm**) and the airvent holes being (**10mm x 37mm**) and **10mm** from the top edges of all the walls. The door is (**93.32mm x 126.32mm**) with a door knob and hinge holes. 

with fillets being **1 mm**. the wire cutout is (**2mm x 3.50mm**) at the bottom edge of the *battery cutout*. 









### Summary

The CAD design went through **many** changes as it progressed like the **airvent holes**, design of the **Top** being the major ones. But many small changes occured as we moved forward like the percise measurment of the **Arduino MKR** screw holes, the measurments of the **windgauge**, and the wire holes for all of them.




