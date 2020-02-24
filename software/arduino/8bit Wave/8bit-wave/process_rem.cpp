#include <Arduino.h>
#include <TMRpcm.h>
#include "constants.h"
#include "commands.h"
extern bool isstopped;
extern bool ispaused;
extern bool mctrl;
extern TMRpcm Taudio;

void initialize_rem() { 
  pinMode(REM, INPUT_PULLUP);
  digitalWrite(REM, HIGH);
}

void process_rem() {
  // if motorcontrol engage
  if (digitalRead(REM) == HIGH && mctrl && Taudio.isPlaying()) {
    if (!isstopped && !ispaused) {
      motor_off();
    }
  }

  if (digitalRead(REM) == LOW && mctrl) {
    if (!isstopped) {
      motor_on();
    }
  }
}

bool is_rem_active() {
  if (!mctrl) return false;
  return digitalRead(REM) == HIGH;
}