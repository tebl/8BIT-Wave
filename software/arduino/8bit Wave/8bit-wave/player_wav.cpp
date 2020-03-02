#include <Arduino.h>
#include <TMRpcm.h>
#include "constants.h"

#define VOLUME_MIN 0
#define VOLUME_MAX 7

extern volatile byte player_state;
int volume = 3;

TMRpcm Taudio;


/*
 * Check if the extension of the filename currently specified matches that of
 * a wav-file.
 */
bool wav_is_supported(const char * filename) {
  const size_t length = strlen(filename);
  if (length < 5) return false;
  if (!(filename[length - 4] == '.')) return false;
  if (!(filename[length - 3] == 'w' || filename[length - 3] == 'W')) return false;
  if (!(filename[length - 2] == 'a' || filename[length - 2] == 'A')) return false;
  if (!(filename[length - 1] == 'v' || filename[length - 1] == 'V')) return false;
  return true;
}

/* 
 * Check if the player is currently running, this does not count any of the
 * paused states as running. If we are running, we'll check if the player
 * stopped since we last checked it before returning. There's a race-condition
 * here, but without a dedicated resume function it's as close as we get.
 */
bool wav_is_running() {
  if (player_state == PLAYER_RUNNING && !Taudio.isPlaying()) {
    player_state = PLAYER_IDLE;
  }
  return player_state == PLAYER_RUNNING;
}

/*
 * Check wether the player has been actively stopped by the user and not by any
 * other means (player stopped by itself or paused by REM).
 */
bool wav_is_paused() {
  return player_state == PLAYER_PAUSED;
}

/*
 * Pause the player if possible, returns wether the player is actually paused at
 * the end - this is done to ensure that the states haven't changed for any other
 * reason such as either no longer playing or paused by REM(ote). 
 */
bool wav_pause() {
  if (wav_is_running()) {
    Taudio.pause();
    player_state = PLAYER_PAUSED;
  }
  return wav_is_paused();
}

/*
 * Resume playing the file if possible, but note that this may not be possible if
 * the player had been paused by REM(ote) or some other unforseen thing happening
 * along the way.
 */
bool wav_resume() {
  if (wav_is_paused()) {
    Taudio.pause();
    player_state = PLAYER_RUNNING;
  }
  return !wav_is_paused();
}

/*
 * Check wether the player has been started, but note that it may have been
 * paused by the user or via REM(ote).
 */
bool wav_is_started() {
  switch (player_state) {
    case PLAYER_IDLE:
      return false;
    case PLAYER_RUNNING:
      return wav_is_running();
    case PLAYER_PAUSED:
    case PLAYER_MOTOR_OFF:
    default:
      return true;
  }
  return false;
}

/*
 * Determine if the player has been turned off via REM(ote), if that function
 * is available.
 */
bool wav_is_motor_off() {
  return player_state == PLAYER_MOTOR_OFF;
}

/*
 * Turn off the player with the REM(ote) being the source, this also ensures
 * that the user can no longer resume the tape by himself and in this way 
 * allow the tape to get ahead of the program.
 */
bool wav_motor_off() {
  if (wav_is_running()) {
    Taudio.pause();
    player_state = PLAYER_MOTOR_OFF;
  }
  return wav_is_motor_off();
}

/*
 * Resume playing when previously paused via REM(ote).
 */
bool wav_motor_on() {
  if (wav_is_motor_off()) {
    player_state = PLAYER_RUNNING;
    Taudio.pause();
  }
  return wav_motor_off();
}

/*
 * Start the player
 */
void wav_start(char* filename) {
  Taudio.play(filename);
  player_state = PLAYER_RUNNING;
}

/*
 * Should ensure that the player stopped, or at least as close as we are able
 * to get before returning. We are using is_started here just in case the
 * player has been paused, either directly or via motor REM(ote).
 */
void wav_stop() {
  if (wav_is_started()) {
    Taudio.stopPlayback();
  }
  player_state = PLAYER_IDLE;
}

/*
 * Get current volume in percentage
 */
int wav_volume() {
  return map(volume, VOLUME_MIN, VOLUME_MAX, 0, 100);
}

/*
 * Set the player volume as indicated, return value will be a percentage with
 * minimum and maximum bounds taken into account.
 */
int wav_volume(int new_value) {
  if (new_value < VOLUME_MIN) new_value = VOLUME_MIN;
  if (new_value > VOLUME_MAX) new_value = VOLUME_MAX;

  volume = new_value;
  Taudio.setVolume(new_value);
  return wav_volume();
}

int wav_volume_up() {
  return wav_volume(volume + 1);
}

int wav_volume_down() {
  return wav_volume(volume - 1);
}

void initialize_wav_player() {
  Taudio.speakerPin = AUDIO_OUT;
  wav_volume(volume);
}