#include <NTPClient.h>
// change next line to use with another board/shield
#include <WiFiNINA.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>

const char SSID[] = "CHS Guest Wireless";   // your network SSID (name)
const char PASSWORD[] = "";   // your network password (use for WPA, or use as key for WEP)

WiFiUDP ntpUDP;

// You can specify the time server pool and the offset, (in seconds)
// additionally you can specify the update interval (in milliseconds).
 NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", -3600, 60000);

void setup(){
  Serial.begin(115200);
  WiFi.begin(SSID, PASSWORD);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
}

void loop() {
  timeClient.update();

  Serial.println(timeClient.getFormattedTime());

  delay(1000);
}