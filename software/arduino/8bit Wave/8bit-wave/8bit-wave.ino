#include <Arduino.h>
#include <TMRpcm.h>
#include "constants.h"
#include "typedefs.h"
#include "led_control.h"
#include "display.h"
#include "notice.h"
#include "process_switches.h"
#include "process_rem.h"
#include "process_sd.h"
#include "scrolling.h"
#include "commands.h"

char filename[FILENAME_MAX_LENGTH];

bool mctrl = 0;
TMRpcm Taudio;
int volume = 3;
bool ispaused = false;
bool isstopped = true;
#define TEXT_PLAY "PLAY A WAV:"
#define TEXT_PLAYING "Playing:"
#define TEXT_PAUSED "Paused!"

SwitchFunctions switch_functions;

void (*resetFunc)(void) = 0;
void setup();
void loop();

void tick();
void check_audio_done();
void callback_initialize();


void setup() {
  Serial.begin(9600);

  /* Setup pins */
  Taudio.speakerPin = 9;

  /* Initialie subsystems */
  initialize_led();
  initialize_display();
  initialize_rem();
  initialize_switches();
  callback_initialize();
  display_welcome();
  set_volume(volume, true);

  // First Msg
  memset(filename, 0, sizeof(filename));
  display_set(OLED_LINE_0, F(TEXT_PLAY));
  set_notice("(loading SD)");
}

void loop() {
  clear_notice();

  if (process_sd());
  else tick();

  process_switches();
  process_rem();
}

unsigned long next_tick = millis() + TICK_LENGTH;
void tick() {
  if (next_tick < millis()) {
    check_audio_done();
    scroll_filename();
    led_tick();
    next_tick = millis() + TICK_LENGTH;
  }
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
    set_notice("(No file!)");
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
    ispaused = true;
  } else {
    display_set(OLED_LINE_0, F(TEXT_PLAYING));
    display_set(OLED_LINE_1, filename);
    set_led_cycle(LED_POWER);
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
      }
    }
  }
}

// stop a file
void do_stop() {
  Taudio.stopPlayback();
  display_set(OLED_LINE_0, F(TEXT_PLAY));
  set_led_neutral(LED_POWER);
  isstopped = true;
}

void press_stop() {
  if (Taudio.isPlaying()) {
    do_stop();
    scroll_sync();
  }
}

/*
 * Run regularly to verify that audio is currently playing, if it has stopped
 * then we pretend the stop button was pushed really hard.
 */
void check_audio_done() {
  if (!Taudio.isPlaying() and !isstopped) {
    do_stop();
    scroll_sync();
    set_notice("(finished)");
  }
}

void callback_initialize() {
  set_callback(SW_PLAY, press_play, nullptr);
  set_callback(SW_STOP, press_stop, nullptr);
  set_callback(SW_EJECT, toggle_motor_controls, resetFunc);
  set_callback(SW_UP, press_up, increase_volume);
  set_callback(SW_DOWN, press_down, decrease_volume);
}