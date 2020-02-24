#include <Arduino.h>
#include <TMRpcm.h>
#include "constants.h"
#include "notice.h"
#include "commands.h"
extern int volume;
extern bool isstopped;
extern bool ispaused;
extern bool mctrl;
extern TMRpcm Taudio;

/*
 * Toggle motor controls ON/OFF
 */
void toggle_motor_controls() {
  if (mctrl) {
    mctrl = false;
    set_notice("(MotorCtrl OFF)");
  } else {
    mctrl = true;
    set_notice("(MotorCtrl ON)");
  }
}

/*
 * Pause playback through REM plug, this often has an associated basic
 * command on the remote computer listed as motor off.
 */
void motor_off() {
  Taudio.pause();
  set_notice("(Motor OFF)");
  ispaused = true;
}

/*
 * Unpause through REM plug
 */
void motor_on() {
  if (ispaused) {
    Taudio.pause();
    set_notice("(Motor ON)");
    ispaused = false;
  }
}

/*
 * Update audio setting.
 */
void set_volume(int new_setting, bool suppress_notice) {
  if (new_setting < VOLUME_MIN) volume = VOLUME_MIN;
  else if (new_setting > VOLUME_MAX) volume = VOLUME_MAX;
  else volume = new_setting;

  //analogWrite(LED_USER, map(volume, VOLUME_MIN, VOLUME_MAX, LED_USER_MIN, LED_USER_MAX));
  analogWrite(LED_USER, LOW);
  Taudio.setVolume(volume);

  if (!suppress_notice) {
    char message[OLED_LINE_WIDTH];
    sprintf(message, "(Volume %d)", volume);
    set_notice(message);
  }
}

void increase_volume() {
  set_volume(volume + 1);
}

void decrease_volume() {
  set_volume(volume - 1);
}

/*
* Toggle volume settings
*/
void toggle_volume() {
  if (VOLUME_MAX <= volume) set_volume(VOLUME_MIN);
  else increase_volume();
}