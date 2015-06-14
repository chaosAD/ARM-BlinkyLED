#ifndef State_H
#define State_H

typedef enum {
	INITIAL,
	LED_ON,
	LED_OFF,
	WAIT_BUTTON_RELEASE,
	CHECK_BUTTON_STATUS,
	BUTTON_NOT_PRESSED,
	BUTTON_PRESSED
} State;

#endif // State_H
