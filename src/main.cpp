#include <Arduino.h>
#include "gpio_handler.h"
#include "webserver_handler.h"

const char* WIFI_SSID = "Bohra";
const char* WIFI_PASSWORD = "bohra@987";

const uint8_t LED_PIN = 2; // Built-in LED pin on most ESP32 boards

static unsigned long previousMillis = 0;
const long interval = 1000; // interval at which to blink (milliseconds)
unsigned long currentMillis = 0;

WebServerHandler* server = new WebServerHandler(WIFI_SSID, WIFI_PASSWORD);
GPIOHandler* led = new GPIOHandler(LED_PIN);

void setup() {
    // Initialize serial communication
    Serial.begin(115200);

    // Initialize GPIOs
    led->initializeOutput();

    // Initialize WiFi in STA mode
    if(server->connect()) {
        Serial.println("Connected to WiFi");
        Serial.print("IP Address: ");
        Serial.println(server->getIP());
        server->start();
    } else {
        Serial.println("Failed to connect to WiFi");
    }
}

void loop() {

    currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        bool ledState = led->digitalRead();
        led->digitalWrite(!ledState);
    }
    server->handleClient();
}