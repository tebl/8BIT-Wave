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
#include "player.h"

char filename[FILENAME_MAX_LENGTH];

bool is_stopped = true;

/*
 * Update volume setting as provided by the player - note that as the player
 * controls the volume, we can only tell it we want it to change and then
 * report the percentage we got back it.
 */
void volume_changed(int new_setting) {
    char message[OLED_LINE_WIDTH];
    sprintf(message, "(Volume %d%c)", new_setting, '%');
    set_notice(message);

    /* Set volume on USER LED, have it fade out after a while */
    set_led_fade_out(
      LED_USER,
      map(new_setting, 0, 100, LED_USER_MIN, LED_USER_MAX),
      second_to_ticks(10)
    );
}
void increase_volume() { volume_changed(player_volume_up()); }
void decrease_volume() { volume_changed(player_volume_down()); }

void press_up() {
  if (!player_is_started()) {
    previous_file();
  }
}

void press_down() {
  if (!player_is_started()) {
    next_file();
  }
}

void press_pause() {
  if (!player_is_started() || is_stopped) return;
  if (player_is_paused()) {
    if (player_resume()) {
      display_set(OLED_LINE_0, F(TEXT_PLAYING));
      display_set(OLED_LINE_1, filename);
      set_led_cycle(LED_POWER);
      set_timer_resume();
    } 
  } else {
    if (player_pause()) {
      display_set(OLED_LINE_0, F(TEXT_PAUSED));
      set_led_flash(LED_POWER);
      set_timer_pause();
    }
  }
}

void press_play() {
  if (is_stopped) {
    if (is_file_selected()) {
      set_notice(F(ERROR_FILE_NOT_FOUND));
    } else {
      display_set(OLED_LINE_0, F(TEXT_PLAYING));
      display_set(OLED_LINE_1, filename);
      set_led_cycle(LED_POWER);
      set_timer_start();

      player_start(filename);
      is_stopped = false;
    }
  } else {
    press_pause();
  }
}


/*
 * Stop the player from making any more controlled noise. This function will
 * be called either when the stop button has been pushed, or when we detect
 * that the player has stopped in the background without us knowing about it.
 */
void do_stop() {
  player_stop();

  display_set(OLED_LINE_0, F(TEXT_PLAY));
  set_led_neutral(LED_POWER);
  set_timer_stop();

  scroll_sync();
  set_timer_stop();

  is_stopped = true;
}

/*
 * Pressed stop button.
 */
void press_stop() {
  do_stop();
}

/*
 * Run regularly to verify that audio is still playing, if it has stopped
 * then we pretend the stop button was pushed really hard.
 */
void check_audio_done() {
  if (!is_stopped and !player_is_started()) {
    do_stop();
    set_notice(F(NOTICE_DONE));
  }
}

void initialize_commands() {
  memset(filename, 0, sizeof(filename));
  display_set(OLED_LINE_0, F(TEXT_PLAY));
  set_notice(F(NOTICE_LOAD_SD));

  set_callback(SW_PLAY, press_play);
  set_callback(SW_STOP, press_stop, nullptr);
  set_callback(SW_EJECT, nullptr, toggle_motor_controls);
  set_callback(SW_UP, press_up, increase_volume);
  set_callback(SW_DOWN, press_down, decrease_volume);
}