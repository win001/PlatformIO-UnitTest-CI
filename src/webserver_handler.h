#ifndef WEBSERVER_HANDLER_H
#define WEBSERVER_HANDLER_H

#include <WebServer.h>
#include <WiFi.h>

class WebServerHandler {
public:
    WebServerHandler(const char* ssid, const char* password);
    bool connect();
    bool start();
    bool isConnected();
    String getIP();
    void handleClient();

private:
    const char* _ssid;
    const char* _password;
    WebServer _server;
    void setupRoutes();
};

#endif