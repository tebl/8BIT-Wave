#include <Arduino.h>
#include "constants.h"
#include "typedefs.h"

LedSetting led_settings[LED_NUMBER_TOTAL] = {
  { LED_POWER, LED_POWER_MIN, LED_POWER_MAX, LED_MODE_NONE, 0, 0 },
  { LED_USER, LED_USER_MIN, LED_USER_MAX, LED_MODE_NONE, 0, 0 }
};

int get_index_for_led(int pin_number) {
  switch(pin_number) {
      default:
      case LED_POWER: return 0;
      case LED_USER:  return 1;
  }
}

LedSetting* get_led_setting(int pin_number) {
  return &led_settings[get_index_for_led(pin_number)];
}

/*
 * Set the LED back into neutral mode, which just means that it won't do
 * anything by itself anymore.
 */
void set_led_neutral(int pin_number) {
  LedSetting *setting = get_led_setting(pin_number);
  analogWrite(pin_number, 0);
  setting->mode = LED_MODE_NONE;
}

bool is_led_neutral(LedSetting *setting) {
  return setting->mode == LED_MODE_NONE;
}

/*
 * 8BIT Wave flash direct! Flashes the specified LED the specified number of
 * times without caring about any of the automated modes.
 */
void flash_delay() { delay(LED_FLASH_DELAY); }
void flash_led_now(int pin_number, int num_flashes) {
  LedSetting *setting = get_led_setting(pin_number);
  if (!is_led_neutral(setting)) {
    analogWrite(pin_number, LED_MIN);
  }

  for (int i = 0; i < num_flashes; i++) {
  if (i > 0) flash_delay();
      analogWrite(pin_number, setting->max);
      flash_delay();
      analogWrite(pin_number, LED_MIN);
  }

  if (!is_led_neutral(setting)) {
    analogWrite(pin_number, setting->value);
  }
}

/*
 * Process LED changes per tick (as defined by the main thread, so don't set
 * your clock by it).
 */
void do_led_tick(LedSetting *setting) {
  switch(setting->mode) {
    default:
    case LED_MODE_NONE:
      return;

    case LED_MODE_FLASH_ON:
      setting->value = setting->max;
      analogWrite(setting->pin_number, setting->parameter);
      setting->mode = LED_MODE_FLASH_OFF;
      return;

    case LED_MODE_FLASH_OFF:
      setting->value = setting->min;
      analogWrite(setting->pin_number, setting->min);
      setting->mode = LED_MODE_FLASH_ON;
      return;

    case LED_MODE_CYCLE_UP:
      setting->value += LED_STEP;
      if (setting->value > setting->max) {
        setting->value = setting->max;
        setting->mode = LED_MODE_CYCLE_DOWN;
      }
      analogWrite(setting->pin_number, setting->value);
      return; 

    case LED_MODE_CYCLE_DOWN:
      setting->value -= LED_STEP;
      if (setting->value < setting->min) {
        setting->value = setting->min;
        setting->mode = LED_MODE_CYCLE_UP;
      }
      analogWrite(setting->pin_number, setting->value);
      return; 

    case LED_MODE_FADE_OUT:
      if (setting->parameter > 0) {
        setting->parameter--;
        return;
      }

      setting->value -= LED_STEP;
      if (setting->value < 0) {
        setting->value = 0;
        setting->mode = LED_MODE_NONE;
      }
      analogWrite(setting->pin_number, setting->value);
      return; 
  }
}

/*
 * Set the LED to cycle up and down.
 */
void set_led_cycle(int pin_number) {
  LedSetting *setting = get_led_setting(pin_number);
  if (setting->min <= setting->value) {
    setting->mode = LED_MODE_CYCLE_UP;
  } else {
    setting->mode = LED_MODE_CYCLE_DOWN;
  }
}

/*
 * Set the LED to flash on and off.
 */
void set_led_flash(int pin_number, int value) {
  LedSetting *setting = get_led_setting(pin_number);
  if (value < 0) value = setting->max / 2;
  setting->parameter = value;

  if (setting->min < setting->value) {
    setting->mode = LED_MODE_FLASH_OFF;
  } else {
    setting->mode = LED_MODE_FLASH_ON;
  }
}

/*
 * Turns on the specified LED according to value provided, after the set amount
 * of ticks past the LED will start to fade out and then shut off. Note that the
 * behavior may be overridden before finishing.
 */
void set_led_fade_out(int pin_number, int value, int tick_delay) {
  LedSetting *setting = get_led_setting(pin_number);
  setting->mode = LED_MODE_FADE_OUT;
  setting->parameter = tick_delay;
  if (value < 0) value = setting->max;
  setting->value = value;
  analogWrite(pin_number, setting->value);
}

/*
 * Translates the main threads tick counter so that we can have a consistent
 * duration in seconds instead.
 */
int second_to_ticks(int num_seconds) {
  return (1000 / TICK_LENGTH) * num_seconds;
}

/*
 * Initialize LEDs by setting their default values upon start-up.
 */
void initialize_led() {
  pinMode(LED_POWER, OUTPUT);
  analogWrite(LED_POWER, LED_POWER_MAX);
  set_led_fade_out(LED_POWER, LED_POWER_MAX, second_to_ticks(6));

  pinMode(LED_USER, OUTPUT);
  analogWrite(LED_USER, 0);
}

/*
 * Called regularly from main program to regularly have the routines update
 * the LEDs according to their current settings. Each tick is determined by
 * TICK_LENGTH, depending on how much time spent doing everything else.
 */
void led_tick() {
  do_led_tick( &led_settings[get_index_for_led(LED_POWER)] );
  do_led_tick( &led_settings[get_index_for_led(LED_USER)] );
}