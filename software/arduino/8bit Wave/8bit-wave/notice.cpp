#include <Arduino.h>
#include "constants.h"
#include "display.h"
unsigned long notice_timeout = 0;

/*
 * Set a notice that should be shown for a set duration and then removed from
 * the display. Note that later notices will overwrite the current one to keep
 * things responsive.
 */
void set_notice(const char *string) {
  display_set(OLED_LINE_2, string, -1);
  notice_timeout = millis() + NOTICE_DURATION;
}

/*
 * Same thing except the string data is coming out of Flash memory, so you're
 * supposed to figure out how to make that look nice by yourself (add spaces)!
 */
void set_notice(const __FlashStringHelper *string) {
  display_set(OLED_LINE_2, string);
  notice_timeout = millis() + NOTICE_DURATION;
}

/*
 * Check if the current notice has expired, clear it from the display if it has
 * already done so.
 */
void clear_notice() {
  if (notice_timeout == 0) return;
  if (notice_timeout <= millis()) {
    notice_timeout = 0;
    display_set(OLED_LINE_2);
  }
}