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