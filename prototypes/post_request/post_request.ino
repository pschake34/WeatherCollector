// Paul Schakel
// wifi_connection.ino
// Connects to a specified WiFi network and prints the IP Address and other info

#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>
#include "SSID_info.h"

int status = WL_IDLE_STATUS;     // the Wifi radio's status
const char serverName[] = "chsweather.pythonanywhere.com";  // server name
int port = 80;

WiFiClient wifi;
HttpClient client = HttpClient(wifi, serverName, port);

void setup() {
    Serial.begin(9600);
    delay(5000); //wait for serial to start
    Serial.println("Started Serial...");

    while (status != WL_CONNECTED) {
        Serial.print("Attempting to connect to network: ");
        Serial.println(SSID);
        // Connect to WPA/WPA2 network:
        status = WiFi.begin(SSID, PASSWORD);

        // wait 10 seconds for connection:
        delay(10000);
    }

    // you're connected now
    Serial.println("You're connected to the network");

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
}

void loop() {
    Serial.println("making POST request");
    String contentType = "application/json";
    String postData = "{\"name\": \"temperature\",\"value\": 73.69910430908203}";

    client.post("/send_sensor_data", contentType, postData);

    // read the status code and body of the response
    int statusCode = client.responseStatusCode();
    Serial.print("Status code: ");
    Serial.println(statusCode);
    String response = client.responseBody();
    Serial.print("Response: ");
    Serial.println(response);

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

    Serial.println("Wait 10 seconds");
    delay(10000);
}