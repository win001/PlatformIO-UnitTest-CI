#include <unity.h>
#include <Arduino.h>

// Function to be tested
int add(int a, int b) {
    return a + b;
}

bool isEven(int n) {
    return n % 2 == 0;
}

void test_addition(void) {
    TEST_ASSERT_EQUAL(1, isEven(2));
    TEST_ASSERT_EQUAL(1, isEven(0));
    TEST_ASSERT_EQUAL(0, isEven(3));

    TEST_ASSERT_EQUAL(3, add(1, 2));
    TEST_ASSERT_EQUAL(5, add(2, 3));
    TEST_ASSERT_EQUAL(7, add(3, 4));
}

void setup() {
    delay(2000);  // Allow board to settle
    UNITY_BEGIN();
    RUN_TEST(test_addition);
    UNITY_END();
}

void loop() {
}