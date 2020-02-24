#include <Arduino.h>
#include <SPI.h>
#include <TMRpcm.h>
#include <Wire.h>
#include "SdFat.h"
#include "constants.h"
#include "typedefs.h"
#include "led_control.h"
#include "display.h"
#include "notice.h"
#include "process_switches.h"
#include "process_rem.h"
#include "commands.h"

#define FILENAME_MAX_LENGTH 100
char filename[FILENAME_MAX_LENGTH];

bool mctrl = 0;
TMRpcm Taudio;
int volume = 3;
bool ispaused = false;
bool isstopped = true;
const uint8_t SD_CS_PIN = SS;
const char *playwaymsg = "PLAY A WAV:";
SdFat sd;

SwitchFunctions switch_functions;

void (*resetFunc)(void) = 0;
void setup();
void loop();
bool is_wav(const char *string);

bool process_sd();
bool check_sd_inserted();
void get_sd_position();

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
  //display_welcome();
  set_volume(volume, true);

  // First Msg
  memset(filename, 0, sizeof(filename));
  display_set(OLED_LINE_0, playwaymsg);
  set_notice("(loading SD)");
}

void loop() {
  clear_notice();

  if (process_sd());
  else tick();

  process_switches();
  process_rem();
}

bool sd_dirty = true;
bool process_sd() {
  if (sd_dirty) {
    check_sd_inserted();
    get_sd_position();
    sd_dirty = false;
    return true;
  }
  return false;
}

/*
 * Ensures that the SD card has been inserted, will block indefinitely until we
 * actually detect the card - this is done before any other processing if
 * needed.
 */
bool check_sd_inserted() {
  while(!sd.begin(SD_CS_PIN, SD_SCK_MHZ(50))) {
    set_notice("Card not found!");
    delay(1000);
  }
  return true;
}

/*
 * Handles scrolling the filename across line 1 of the display, but in note that
 * in order to keep things moving at a sort of acceptable speed we'll need manual
 * sync every time the filename changes.
 */
int scroll_length = 0;
int scroll_index = 0;
void scroll_filename() {
  if (!Taudio.isPlaying()) {
    display_set(OLED_LINE_1, filename, scroll_index);
    if (scroll_index <= scroll_length) scroll_index++;
    else scroll_index = 0;
  }
}

/*
 * Notifies the scrolling mechanism that the data has changed, so we should
 * probably start at the beginning again.
 */
void scroll_sync() {
  scroll_length = strlen(filename);
  scroll_index = 0;
}

/*
 * Check if the extension of the filename currently specified matches that of
 * a wav-file.
 */
bool is_wav(const char *string) {
  const size_t length = strlen(string);
  if (length < 5) return false;
  if (!(string[length - 4] == '.')) return false;
  if (!(string[length - 3] == 'w' || string[length - 3] == 'W')) return false;
  if (!(string[length - 2] == 'a' || string[length - 2] == 'A')) return false;
  if (!(string[length - 1] == 'v' || string[length - 1] == 'V')) return false;
  return true;
}

/*
 * Given a previously known file index, attempts to step through the
 * directory contents on the SD card root. The routine will either stop when
 * we encounter the end of the directory or we've counted up until the we get
 * to the file that we want.
 */
int file_index = 0;
void get_sd_position() {
  SdFile a_file;
  SdFile root;
  
  if (!root.open("/", O_RDONLY)) {
    sd.errorHalt("open root failed");
    set_notice("(SD read error)");
    delay(2000);
    return;
  }

  int counted = -1;
  while (a_file.openNext(&root, O_RDONLY)) {
    if (!a_file.isSubDir() && !a_file.isHidden()) {
      memset(filename, 0, sizeof(filename));
      if (a_file.getName(filename, FILENAME_MAX_LENGTH)) {
        if (is_wav(filename)) {
          if (counted == -1) counted = 0;
          else counted++;
        }
      }
    }

    a_file.close();
    if (file_index == counted) break;
  }
  if (counted < file_index) file_index = counted;

  if (file_index >= 0) {
    scroll_sync();
    display_set(OLED_LINE_1, filename);
  } else {
    display_set(OLED_LINE_1);
    set_notice("(No files!)");
    delay(2000);
  }
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

void do_previous_file() {
  if (file_index > 0) {
    file_index--;
  }
  sd_dirty = true;
}

void press_up() {
  if (!Taudio.isPlaying()) {
    do_previous_file();
  }
}

void do_next_file() {
  file_index++;
  sd_dirty = true;
}

void press_down() {
  if (!Taudio.isPlaying()) {
    do_next_file();
  }
}

void do_play() {
  if (file_index == -1) {
    set_notice("(No file!)");
  } else {
    isstopped = false;
    display_set(OLED_LINE_0, "Playing:");
    display_set(OLED_LINE_1, filename);
    set_led_cycle(LED_POWER);
    Taudio.play(filename);
  }
}

// pause a file
void do_pause() {
  Taudio.pause();
  if (!ispaused) {
    display_set(OLED_LINE_0, "Paused!");
    set_led_flash(LED_POWER);
    ispaused = true;
  } else {
    display_set(OLED_LINE_0, "Playing:");
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
  display_set(OLED_LINE_0, playwaymsg);
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