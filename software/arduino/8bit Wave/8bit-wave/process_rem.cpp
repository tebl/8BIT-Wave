#include <Arduino.h>
#include <TMRpcm.h>
#include "constants.h"
#include "notice.h"
#include "commands.h"
#include "player.h"

bool rem_enabled = false;

void initialize_rem() { 
  pinMode(REM, INPUT_PULLUP);
  digitalWrite(REM, HIGH);
}

void set_rem_enabled(bool value) {
  rem_enabled = value;
}

bool is_rem_enabled() {
  return rem_enabled;
}

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
 * Determines if REM has been asserted, in the case of the Amstrad CPC this
 * means that the cassette drive motor should be on when the contacts have
 * been closed (meaning low). Arduino adds a pull-up to this line when it
 * would otherwise have been left floating.
 */
bool is_rem_asserted() {
  if (!is_rem_enabled()) return false;
  return digitalRead(REM) == LOW;
}

void process_rem() {
  if (!is_rem_enabled()) return;

  if (is_rem_asserted()) {
    if (player_is_running()) {
      player_motor_off();
      set_timer_resume();
      set_notice(F(NOTICE_MOTOR_ON));
    }
  } else {
    if (player_is_motor_off()) {
      player_motor_on();
      set_timer_pause();
      set_notice(F(NOTICE_MOTOR_OFF));
    }
  }
}