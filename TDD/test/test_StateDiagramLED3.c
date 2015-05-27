#include "unity.h"
#include "Utils.h"
#include "StateDiagramLED3.h"
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

    readUserButton_ExpectAndReturn(0);

    state = blinkLED3(state);

    TEST_ASSERT_EQUAL(INITIAL, state);
}
