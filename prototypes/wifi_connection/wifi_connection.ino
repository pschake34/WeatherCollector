// Paul Schakel
// wifi_connection.ino
// Connects to a specified WiFi network and prints the IP Address and other info

#include <WiFiNINA.h>
#include "SSID_info.h"

int status = WL_IDLE_STATUS;     // the Wifi radio's status

void setup() {
    Serial.begin(115200);

    while(!Serial){}
    Serial.println("Started Serial...");

    while (status != WL_CONNECTED) {
        Serial.print("Attempting to connect to network: ");
        Serial.println(SSID);
        Serial.println(PASSWORD);
        // Connect to WPA/WPA2 network:
        status = WiFi.begin(SSID, PASSWORD);

        // wait 10 seconds for connection:
        delay(10000);
    }

    // you're connected now
    Serial.println("You're connected to the network");
}

void loop() {
    Serial.println("\nInformation: ");

    // print your board's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print the received signal strength:
    long rssi = WiFi.RSSI();
    Serial.print("Signal strength (RSSI):");
    Serial.println(rssi);

    delay(5000);
}