#include <Arduino.h>
#include <TMRpcm.h>
#include "constants.h"
#include "notice.h"
#include "display.h"
#include "led_control.h"
#include "process_sd.h"
#include "process_switches.h"
#include "process_rem.h"
#include "scrolling.h"

char filename[FILENAME_MAX_LENGTH];
int volume = 3;

extern int volume;
extern bool isstopped;
extern bool ispaused;
extern TMRpcm Taudio;

/*
 * Toggle motor controls ON/OFF. This is called when holding down the eject
 * button.
 */
void toggle_motor_controls() {
  if (is_rem_enabled()) {
    set_rem_enabled(false);
    set_notice(F(NOTICE_MOTOR_CTRL_OFF));
  } else {
    set_rem_enabled(true);
    set_notice(F(NOTICE_MOTOR_CTRL_ON));
  }
}

/*
 * Pause playback through REM plug, this often has an associated basic
 * command on the remote computer listed as motor off.
 */
void motor_off() {
  Taudio.pause();
  set_timer_pause();
  set_notice(F(NOTICE_MOTOR_OFF));
  ispaused = true;
}

/*
 * Unpause through REM plug
 */
void motor_on() {
  if (ispaused) {
    Taudio.pause();
    set_timer_resume();
    set_notice(F(NOTICE_MOTOR_ON));
    ispaused = false;
  }
}

/*
 * Update audio setting, if possible (the setting will be be corrected for
 * upper and lower bounds). Suppressing the notice is used when it is not
 * required, such as when syncinc the value upon startup.
 */
void set_volume(int new_setting, bool suppress_notice) {
  if (new_setting < VOLUME_MIN) volume = VOLUME_MIN;
  else if (new_setting > VOLUME_MAX) volume = VOLUME_MAX;
  else volume = new_setting;

  Taudio.setVolume(volume);
  if (!suppress_notice) {
    char message[OLED_LINE_WIDTH];
    sprintf(message, "(Volume %d)", volume);
    set_notice(message);

    /* Set volume on USER LED, have it fade out after a while */
    set_led_fade_out(
      LED_USER,
      map(volume, VOLUME_MIN, VOLUME_MAX, LED_USER_MIN, LED_USER_MAX),
      second_to_ticks(10)
    );
  }
}

void increase_volume() {
  set_volume(volume + 1, false);
}

void decrease_volume() {
  set_volume(volume - 1, false);
}

/*
* Toggle volume settings
*/
void toggle_volume() {
  if (VOLUME_MAX <= volume) set_volume(VOLUME_MIN, false);
  else increase_volume();
}

void press_up() {
  if (!Taudio.isPlaying()) {
    previous_file();
  }
}

void press_down() {
  if (!Taudio.isPlaying()) {
    next_file();
  }
}

void do_play() {
  if (is_file_selected()) {
    set_notice(F(ERROR_FILE_NOT_FOUND));
  } else {
    isstopped = false;
    display_set(OLED_LINE_0, F(TEXT_PLAYING));
    display_set(OLED_LINE_1, filename);
    set_led_cycle(LED_POWER);
    Taudio.play(filename);
  }
}

// pause a file
void do_pause() {
  Taudio.pause();
  if (!ispaused) {
    display_set(OLED_LINE_0, F(TEXT_PAUSED));
    set_led_flash(LED_POWER);
    set_timer_pause();
    ispaused = true;
  } else {
    display_set(OLED_LINE_0, F(TEXT_PLAYING));
    display_set(OLED_LINE_1, filename);
    set_led_cycle(LED_POWER);
    set_timer_resume();
    ispaused = false;
  }
}

void press_play() {
  if (Taudio.isPlaying()) {
    if (!isstopped) {
      do_pause();
    }
  } else {
    if (isstopped || ispaused) {
      if (!is_rem_active()) {
        do_play();
        set_timer_start();
      }
    }
  }
}

// stop a file
void do_stop() {
  Taudio.stopPlayback();
  display_set(OLED_LINE_0, F(TEXT_PLAY));
  set_led_neutral(LED_POWER);
  set_timer_stop();
  ispaused = false;
  isstopped = true;
}

void press_stop() {
  if (Taudio.isPlaying()) {
    do_stop();
    scroll_sync();
  } else {
    /* ensure timer stopped */
  } 
  set_timer_stop();
}

/*
 * Run regularly to verify that audio is currently playing, if it has stopped
 * then we pretend the stop button was pushed really hard.
 */
void check_audio_done() {
  if (!Taudio.isPlaying() and !isstopped) {
    do_stop();
    scroll_sync();
    set_notice(F(NOTICE_DONE));
  }
}

void initialize_commands() {
  memset(filename, 0, sizeof(filename));
  display_set(OLED_LINE_0, F(TEXT_PLAY));
  set_notice(F(NOTICE_LOAD_SD));

  set_volume(volume, true);

  set_callback(SW_PLAY, press_play);
  set_callback(SW_STOP, press_stop, nullptr);
  set_callback(SW_EJECT, nullptr, toggle_motor_controls);
  set_callback(SW_UP, press_up, increase_volume);
  set_callback(SW_DOWN, press_down, decrease_volume);
}