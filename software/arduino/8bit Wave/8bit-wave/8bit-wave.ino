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

bool mctrl = 0;
TMRpcm Taudio;
bool ispaused = false;
bool isstopped = true;

void setup() {
  Serial.begin(9600);

  /* Setup pins */
  Taudio.speakerPin = 9;

  /* Initialie subsystems */
  initialize_led();
  initialize_display();
  initialize_rem();
  initialize_switches();

  display_welcome();
  initialize_commands();
}

unsigned long next_tick = millis() + TICK_LENGTH;
void tick() {
  if (next_tick < millis()) {
    check_audio_done();
    scroll_filename();
    led_tick();
    update_timer();
    next_tick = millis() + TICK_LENGTH;
  }
}

void loop() {
  clear_notice();

  if (process_sd());
  else tick();

  process_switches();
  process_rem();
}