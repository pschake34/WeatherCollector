// Paul Schakel
// MKR_Carrier_LCD.ino
// Prototype testing out the display and buttons on the MKR IoT Carrier

#include <Arduino_MKRIoTCarrier.h>

MKRIoTCarrier carrier;

int count = 0;
bool hasCounted = false;
bool hasChanged = true;

void setup() {
    Serial.begin(115200);

    while(!Serial){}
    Serial.println("Started Serial...");

    //Set if it has the Enclosure mounted
    CARRIER_CASE = false;
    //Initialize the IoTSK carrier and output any errors in the serial monitor
    carrier.begin();

    carrier.display.fillScreen(ST7735_BLUE);
    carrier.display.setTextColor(ST7735_WHITE);
    carrier.display.setTextSize(6);
    carrier.display.setCursor(0, 0);
    carrier.display.println("Hello World!");
    delay(5000);
}

void loop() {
    carrier.Buttons.update();

    if (carrier.Button0.onTouchDown() && !hasCounted) {
        count++;
        hasChanged = true;
    } else if (carrier.Button1.onTouchDown() && !hasCounted) {
        count--;
        hasChanged = true;
    } else if ((carrier.Button0.onTouchUp() || carrier.Button1.onTouchUp()) && hasCounted) {
        hasCounted = false;
    } 

    if (hasChanged) {
        carrier.display.fillScreen(ST7735_BLUE);
        carrier.display.setTextSize(5);
        carrier.display.setCursor(0, 0);
        carrier.display.print("Count: ");
        carrier.display.setTextSize(4);
        carrier.display.println(count);
        hasChanged = false;
    }
}