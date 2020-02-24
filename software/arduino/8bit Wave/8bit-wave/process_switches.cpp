#include <Arduino.h>
#include "constants.h"
#include "typedefs.h"
#include "led_control.h"
extern SwitchFunctions switch_functions;

#define STATE_WAIT 0
#define STATE_CHECK1 1
#define STATE_CHECK2 2
#define STATE_WAIT_RELEASE 3
int switch_state[SW_NUMBER_TOTAL];

#define ACTION_NONE 0
#define ACTION_RUN1 1
#define ACTION_RUN2 2
int switch_action[SW_NUMBER_TOTAL];

#define DEBOUNCE_TIME1 50
#define DEBOUNCE_TIME2 1500
unsigned long debounce_time[SW_NUMBER_TOTAL];

void initialize_switches() {
    pinMode(SW_PLAY, INPUT_PULLUP);
    digitalWrite(SW_PLAY, HIGH);
    pinMode(SW_STOP, INPUT_PULLUP);
    digitalWrite(SW_STOP, HIGH);
    pinMode(SW_UP, INPUT_PULLUP);
    digitalWrite(SW_UP, HIGH);
    pinMode(SW_DOWN, INPUT_PULLUP);
    digitalWrite(SW_DOWN, HIGH);
    pinMode(SW_EJECT, INPUT_PULLUP);
    digitalWrite(SW_EJECT, HIGH);
}

int get_index_for_switch(int pin_number) {
    switch(pin_number) {
        default:
        case SW_PLAY:   return 0;
        case SW_STOP:   return 1;
        case SW_EJECT:  return 2;
        case SW_UP:     return 3;
        case SW_DOWN:   return 4; 
    }
}

SwitchCallback* get_callbacks_for(int index) {
    return &switch_functions.functions[index];
}

void set_callback(int pin_number, void (*short_press)(), void (*long_press)()) {
    int index = get_index_for_switch(pin_number);
    SwitchCallback *callbacks = get_callbacks_for(index);
    callbacks->short_press = short_press;
    callbacks->long_press = long_press;
}

void check_switch(const int pin_number) {
    int index = get_index_for_switch(pin_number);
    SwitchCallback *callbacks = get_callbacks_for(index);

    if (callbacks->short_press == nullptr && callbacks->long_press == nullptr) return;

    if (digitalRead(pin_number) == LOW) {
        switch (switch_state[index]) {
            case STATE_WAIT:
                debounce_time[index] = millis();
                switch_state[index]++;
                break;
            case STATE_CHECK1:
                if ((millis() - debounce_time[index]) > DEBOUNCE_TIME1) {
                    if (callbacks->short_press != nullptr) {
                        #ifdef SW_FLASH_FIRST
                        flash_led_now(LED_USER, 1);
                        #endif
                        switch_action[index] = ACTION_RUN1;
                    }
                    switch_state[index]++;
                }
                break;
            case STATE_CHECK2:
                if ((millis() - debounce_time[index]) > DEBOUNCE_TIME2) {
                    if (callbacks->long_press != nullptr) {
                        #ifdef SW_FLASH_SECOND
                        flash_led_now(LED_USER, 2);
                        #endif
                        switch_action[index] = ACTION_RUN2;
                    }
                    switch_state[index]++;
                }
                break;
            case STATE_WAIT_RELEASE:
            default:
                delay(DEBOUNCE_TIME1);
                break;
        }
    } else {
        switch(switch_action[index]) {
            case ACTION_RUN1:
                if (callbacks->short_press != nullptr) (*callbacks->short_press)();
                break;
            case ACTION_RUN2:
                if (callbacks->long_press != nullptr) (*callbacks->long_press)();
                break;
        }
        switch_state[index] = STATE_WAIT;
        switch_action[index] = ACTION_NONE;
    }
}

void process_switches() {
    check_switch(SW_PLAY);
    check_switch(SW_STOP);
    check_switch(SW_EJECT);
    check_switch(SW_UP);
    check_switch(SW_DOWN);
}