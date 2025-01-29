#include "webserver_handler.h"

WebServerHandler::WebServerHandler(const char* ssid, const char* password) 
    : _ssid(ssid), _password(password), _server(80) {}

bool WebServerHandler::connect() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(_ssid, _password);
    
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(500);
        attempts++;
    }
    
    return WiFi.status() == WL_CONNECTED;
}

bool WebServerHandler::start() {
    setupRoutes();
    _server.begin();
    return true;
}

void WebServerHandler::setupRoutes() {
    _server.on("/", HTTP_GET, [this]() {
        _server.send(200, "text/plain", "Hello from ESP32!");
    });
    _server.onNotFound([this]() {
        _server.send(404, "text/plain", "Not found");
    });
    _server.on("/led", HTTP_GET, [this]() {
        _server.send(200, "text/plain", "LED state: " + String(digitalRead(2)));
    });
    _server.on("/led/on", HTTP_GET, [this]() {
        digitalWrite(2, HIGH);
        _server.send(200, "text/plain", "LED turned on");
    });
    _server.on("/led/off", HTTP_GET, [this]() {
        digitalWrite(2, LOW);
        _server.send(200, "text/plain", "LED turned off");
    });
    _server.on("/led/toggle", HTTP_GET, [this]() {
        digitalWrite(2, !digitalRead(2));
        _server.send(200, "text/plain", "LED toggled");
    });
}

bool WebServerHandler::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

String WebServerHandler::getIP() {
    return WiFi.localIP().toString();
}

void WebServerHandler::handleClient() {
    _server.handleClient();
}