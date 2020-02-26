#include <Arduino.h>
#include <TMRpcm.h>
#include "constants.h"
#include "commands.h"
extern bool isstopped;
extern bool ispaused;
extern TMRpcm Taudio;

bool rem_enabled = false;

void initialize_rem() { 
  pinMode(REM, INPUT_PULLUP);
  digitalWrite(REM, HIGH);
}

void process_rem() {
  if (digitalRead(REM) == HIGH && rem_enabled && Taudio.isPlaying()) {
    if (!isstopped && !ispaused) {
      motor_off();
    }
  }

  if (digitalRead(REM) == LOW && rem_enabled) {
    if (!isstopped) {
      motor_on();
    }
  }
}

void set_rem_enabled(bool value) {
  rem_enabled = value;
}

bool is_rem_enabled() {
  return rem_enabled;
}

bool is_rem_active() {
  if (!rem_enabled) return false;
  return digitalRead(REM) == HIGH;
}