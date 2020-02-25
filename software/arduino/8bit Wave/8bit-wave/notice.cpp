#include <Arduino.h>
#include "constants.h"
#include "display.h"

#define MILLIS_PER_SECOND 1000
#define SECONDS_PER_MINUTE 60
#define MINUTES_PER_HOUR 60
#define SECONDS_PER_HOUR (SECONDS_PER_MINUTE * MINUTES_PER_HOUR)
#define SECONDS_PER_DAY (SECONDS_PER_HOUR * 24L)

unsigned long notice_timeout = 0;
unsigned long timer_timeout = 0;
unsigned long timer_start = 0;
unsigned int timer_last = -1;
bool timer_running = false;

/*
 * Determine if a notice is currently active on the screen.
 */
bool is_notice_active() {
  return (notice_timeout > 0);
}


/*
 * Determine if a timer is active, note that this function considers a
 * paused timer as active. 
 */
bool is_timer_active() {
  return (timer_start > 0);
}

/*
 * Pause the timer, we store the time already counted up in the timer_start
 * function so that the timer can resume from where we stopped it. 
 */
void set_timer_pause() {
  if (timer_running) {
    timer_start = millis() - timer_start;
    timer_running = false;
  }
}

/*
 * Resume the previously paused timer, timer_start should already hold the
 * time already counted before the timer was paused. 
 */
void set_timer_resume() {
  if (!timer_running) {
    timer_start = millis() - timer_start;
    timer_running = true;
  }
}

/*
 * Stop the on-screen timer - update_timer, when called from the main thread
 * will take care of removing the actual counter display from the screen.
 */
void set_timer_stop() {
  timer_start = 0;
  timer_running = false;
}

/*
 * Start or restart the timer.
 */
void set_timer_start() {
  timer_start = millis();
  timer_running = true;
}

/*
 * Called regularly from main program, should take care of updating the clock
 * shown on screen if one has been started. Note that depending on wether the
 * clock is running or not, the timer_start will either contain elapsed time
 * or time when last resumed.
 */
void update_timer() {
  /* Notice active instead */
  if (is_notice_active()) return;

  /* Expire timer message */
  if (timer_timeout > 0 and timer_timeout < millis()) {
    timer_timeout = 0;
    display_set(OLED_LINE_2);
    return; 
  }

  /* Timer is stopped */
  if (!is_timer_active()) return;

  unsigned long time_now = timer_start / MILLIS_PER_SECOND;
  if (timer_running) time_now = (millis() - timer_start) / MILLIS_PER_SECOND;

  int hours = (time_now % SECONDS_PER_DAY) / SECONDS_PER_HOUR;
  int minutes = (time_now / SECONDS_PER_MINUTE) % SECONDS_PER_MINUTE;
  int seconds = time_now % SECONDS_PER_MINUTE;

  timer_timeout = millis() + NOTICE_DURATION;
  unsigned int sum = hours + minutes + seconds;
  if (sum != timer_last) {
    timer_last = sum;
    display_clock(OLED_LINE_2, hours, minutes, seconds);
  }
}

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
 * Determine if a notice has expired and should be removed from the display.
 */
bool is_notice_expired() {
  if (!is_notice_active()) return false;
  return notice_timeout <= millis();
}

/*
 * Check if the current notice has expired, clear it from the display if it has
 * already done so. Information message should only be shown on the screen when
 * a notice isn't active, but since we don't actively store them a notice active
 * at the beginning will suppress the info message completely.
 */
void clear_notice() {
  if (is_notice_active() && is_notice_expired()) {
    notice_timeout = 0;
    display_set(OLED_LINE_2);
  }
}