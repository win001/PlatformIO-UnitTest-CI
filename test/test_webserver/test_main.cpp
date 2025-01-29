#include <unity.h>
#include "webserver_handler.h"

WebServerHandler* server;
const char* WIFI_SSID = "YourSSID";
const char* WIFI_PASSWORD = "YourPassword";

void setUp(void) {
    server = new WebServerHandler(WIFI_SSID, WIFI_PASSWORD);
}

void tearDown(void) {
    delete server;
}

void test_wifi_connection(void) {
    TEST_ASSERT_TRUE(server->connect());
    delay(1000);
    TEST_ASSERT_TRUE(server->isConnected());
}

void test_server_start(void) {
    TEST_ASSERT_TRUE(server->connect());
    TEST_ASSERT_TRUE(server->start());
    TEST_ASSERT_NOT_EQUAL("0.0.0.0", server->getIP().c_str());
}

void test_wifi_connection_with_timeout(void) {
    unsigned long startTime = millis();
    bool connected = false;
    
    while (millis() - startTime < 10000) { // 10 second timeout
        if (server->connect()) {
            connected = true;
            break;
        }
        delay(500);
    }
    
    TEST_ASSERT_TRUE(connected);
}

void test_wifi_connection_failure(void) {
    WebServerHandler* badServer = new WebServerHandler("wrong_ssid", "wrong_pass");
    TEST_ASSERT_FALSE(badServer->connect());
    delete badServer;
}

void setup() {
    delay(2000); // Allow board to settle
    UNITY_BEGIN();
    
    RUN_TEST(test_wifi_connection);
    RUN_TEST(test_server_start);
    RUN_TEST(test_wifi_connection_with_timeout);
    RUN_TEST(test_wifi_connection_failure);
    
    UNITY_END();
}

void loop() {}