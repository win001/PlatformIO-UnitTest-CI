#include <unity.h>
#include "gpio_handler.h"

GPIOHandler* led;
const uint8_t LED_PIN = 2; // Built-in LED pin on most ESP32 boards

void setUp(void) {
    led = new GPIOHandler(LED_PIN);
}

void tearDown(void) {
    delete led;
}

void test_gpio_output_initialization(void) {
    TEST_ASSERT_TRUE(led->initializeOutput());
}

void test_gpio_input_initialization(void) {
    TEST_ASSERT_TRUE(led->initializeInput());
}

void test_gpio_write_read(void) {
    led->initializeOutput();
    TEST_ASSERT_TRUE(led->digitalWrite(true));
    delay(100);
    TEST_ASSERT_TRUE(led->digitalWrite(false));
}

void setup() {
    delay(2000); // Allow board to settle
    UNITY_BEGIN();
    
    RUN_TEST(test_gpio_output_initialization);
    RUN_TEST(test_gpio_input_initialization);
    RUN_TEST(test_gpio_write_read);
    
    UNITY_END();
}

void loop() {}  