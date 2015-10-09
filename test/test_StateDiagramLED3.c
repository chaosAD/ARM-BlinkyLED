#include <stdlib.h>
#include "unity.h"
#include "StateDiagramLED3.h"
#include "mock_LED.h"
#include "mock_Time.h"
#include "mock_Button.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_blinkLED3_given_INITIAL_state_should_remain_INITIAL_state_if_button_not_pressed(void)
{
	State state = INITIAL;

    turnOffLED_Expect();
    readUserButton_ExpectAndReturn(0);

    state = blinkLED3(state);

    TEST_ASSERT_EQUAL(INITIAL, state);
}

void test_blinkLED3_given_INITIAL_state_should_go_to_LED_OFF_state_if_button_pressed(void)
{
	State state = INITIAL;

    turnOffLED_Expect();
    readUserButton_ExpectAndReturn(1);

    state = blinkLED3(state);

    TEST_ASSERT_EQUAL(LED_OFF, state);
}

void test_blinkLED3_given_LED_OFF_state_should_remain_LED_OFF_state_if_timer_not_expired(void)
{
	State state = LED_OFF;

    isTimerExpire_ExpectAndReturn(ONE_SEC, 0, 0);

    state = blinkLED3(state);

    TEST_ASSERT_EQUAL(LED_OFF, state);
}

void test_blinkLED3_given_LED_OFF_state_should_go_to_LED_ON_state_if_timer_expired(void)
{
	State state = LED_OFF;

    isTimerExpire_ExpectAndReturn(ONE_SEC, 0, 1);
    turnOnLED_Expect();
    getCurrentTime_ExpectAndReturn(0);

    state = blinkLED3(state);

    TEST_ASSERT_EQUAL(LED_ON, state);
}

void test_blinkLED3_given_LED_ON_state_should_remain_LED_ON_state_if_timer_not_expired(void)
{
	State state = LED_ON;

    isTimerExpire_ExpectAndReturn(ONE_SEC, 0, 0);

    state = blinkLED3(state);

    TEST_ASSERT_EQUAL(LED_ON, state);
}

void test_blinkLED3_given_LED_ON_state_should_goto_LED_OFF_state_if_timer_expired(void)
{
	State state = LED_ON;

    isTimerExpire_ExpectAndReturn(ONE_SEC, 0, 1);
    turnOffLED_Expect();
    getCurrentTime_ExpectAndReturn(0);

    state = blinkLED3(state);

    TEST_ASSERT_EQUAL(LED_OFF, state);
}

void test_blinkLED3_given_LED_ON_state_should_goto_WAIT_FOR_RELEASE_state_if_blinkTime_equal_5(void)
{
	State state = LED_ON;

    isTimerExpire_ExpectAndReturn(ONE_SEC, 0, 1);
    turnOffLED_Expect();
    getCurrentTime_ExpectAndReturn(0);

    isTimerExpire_ExpectAndReturn(ONE_SEC, 0, 1);
    turnOnLED_Expect();
    getCurrentTime_ExpectAndReturn(0);

    isTimerExpire_ExpectAndReturn(ONE_SEC, 0, 1);
    turnOffLED_Expect();
    getCurrentTime_ExpectAndReturn(0);

    isTimerExpire_ExpectAndReturn(ONE_SEC, 0, 1);
    turnOnLED_Expect();
    getCurrentTime_ExpectAndReturn(0);

    isTimerExpire_ExpectAndReturn(ONE_SEC, 0, 1);
    turnOffLED_Expect();
    getCurrentTime_ExpectAndReturn(0);

    isTimerExpire_ExpectAndReturn(ONE_SEC, 0, 1);
    turnOnLED_Expect();
    getCurrentTime_ExpectAndReturn(0);

    isTimerExpire_ExpectAndReturn(ONE_SEC, 0, 1);
    turnOffLED_Expect();
    getCurrentTime_ExpectAndReturn(0);

    isTimerExpire_ExpectAndReturn(ONE_SEC, 0, 1);
    turnOnLED_Expect();
    getCurrentTime_ExpectAndReturn(0);

    state = blinkLED3(state);
    state = blinkLED3(state);
    state = blinkLED3(state);
    state = blinkLED3(state);
    state = blinkLED3(state);
    state = blinkLED3(state);
    state = blinkLED3(state);
    state = blinkLED3(state);
    state = blinkLED3(state);

    TEST_ASSERT_EQUAL(WAIT_FOR_RELEASE, state);
}

void test_blinkLED3_given_WAIT_FOR_RELEASE_state_should_remain_WAIT_FOR_RELEASE_state_if_button_pressed(void)
{
	State state = WAIT_FOR_RELEASE;

    turnOffLED_Expect();
    readUserButton_ExpectAndReturn(1);

    state = blinkLED3(state);

    TEST_ASSERT_EQUAL(WAIT_FOR_RELEASE, state);
}

void test_blinkLED3_given_WAIT_FOR_RELEASE_state_should_goto_INITIAL_state_if_button_not_pressed(void)
{
	State state = WAIT_FOR_RELEASE;

    turnOffLED_Expect();
    readUserButton_ExpectAndReturn(0);

    state = blinkLED3(state);

    TEST_ASSERT_EQUAL(INITIAL, state);
}

void test_build_hardware_code_then_flash_into_the_ARM_development_board() {
  system("rake hw:flash");
}