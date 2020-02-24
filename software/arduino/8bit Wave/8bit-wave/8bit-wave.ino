#include <Arduino.h>
#include "constants.h"
#include "SdFat.h"
#include "display.h"
#include <SPI.h>
#include <TMRpcm.h>
#include <Wire.h>

#define scrUpdate 3000
unsigned long time_for_action;
#define posUpdate 500;
unsigned long time_to_move;
char filename[100];
bool mctrl = 0;
TMRpcm Taudio;
int volume = 3;
bool ispaused = false;
bool isstopped = true;
bool hasplayed = false;
const uint8_t SD_CS_PIN = SS;
int filecount = 0;
int fileposition = 0;
int filelength;
const char *playwaymsg = "PLAY A WAV:";
bool sdejected = true;
bool isLCD = false;
SdFat sd;

unsigned long notice_timeout = 0;

void (*resetFunc)(void) = 0;
void getfilecount();
void getfilebatch();
void setup();
void loop();
bool isWav(char *filename);
void playwav();
void pausefile();
void stopplay();
void toggle_motor_controls();
void checksd();
void motor_off();
void motor_on();
void toggle_volume();
void set_volume(int new_setting);

void set_notice(const char *string);
void clear_notice();

void setup() {
  Serial.begin(9600);

  /* Setup pins */
  Taudio.speakerPin = 9;
  pinMode(SW_PLAY, INPUT_PULLUP);
  digitalWrite(SW_PLAY, HIGH);
  pinMode(SW_STOP, INPUT_PULLUP);
  digitalWrite(SW_STOP, HIGH);
  pinMode(SW_UP, INPUT_PULLUP);
  digitalWrite(SW_UP, HIGH);
  pinMode(SW_DOWN, INPUT_PULLUP);
  digitalWrite(SW_DOWN, HIGH);
  pinMode(SW_EJECT, INPUT_PULLUP);
  digitalWrite(SW_EJECT, HIGH);
  pinMode(REM, INPUT_PULLUP);
  digitalWrite(REM, HIGH);
  pinMode(LED_POWER, OUTPUT);
  analogWrite(LED_POWER, 16);
  pinMode(LED_USER, OUTPUT);
  analogWrite(LED_USER, 1);

  /* Initialie subsystems */
  display_initialize();
  //display_welcome();
  set_volume(volume);

  // First Msg
  memset(filename, 0, sizeof(filename));
  strcpy(filename, "Loading up wavs");
  display_set(OLED_LINE_0, playwaymsg);
  display_set(OLED_LINE_1, filename);

  // get initial filecount
  delay(1000);
  getfilecount();
  getfilebatch();
  display_set(OLED_LINE_1, filename);
}

void loop() {
  clear_notice();

  filelength = strlen(filename);
  if (filecount == 0) {
    fileposition = 0;
    getfilecount();
    getfilebatch();
  }
  for (int positionCounter = 0; positionCounter <= filelength;) {
    if (millis() > time_to_move && !Taudio.isPlaying()) {
      time_to_move = millis() + (unsigned long)posUpdate;
      display_set(OLED_LINE_1, filename, positionCounter);
      positionCounter++;
    }
    // scroll if not in play mode
    if (!Taudio.isPlaying()) {
      if (millis() > time_for_action) {
        time_for_action = millis() + (unsigned long)scrUpdate;
        checksd();
        if (sdejected) {
          fileposition = 0;
          getfilecount();
          getfilebatch();
        }
      }

      isstopped = true;
    }

    // check if forward pressed
    if (digitalRead(SW_DOWN) == LOW && !Taudio.isPlaying()) {
      fileposition++;
      if (fileposition >= filecount) {
        fileposition = 0;
      }
      positionCounter = 0;
      getfilebatch();
      break;
    }

    // check if back pressed
    if (digitalRead(SW_UP) == LOW && !Taudio.isPlaying()) {
      fileposition--;
      if (fileposition < 0) {
        fileposition = filecount - 1;
      }
      positionCounter = 0;
      getfilebatch();
      break;
    }

    // if play button pressed
    if (digitalRead(SW_PLAY) == LOW && !Taudio.isPlaying()) {
      if (isstopped || !ispaused) {
        if (digitalRead(REM) == LOW || !mctrl) {
          playwav();
          delay(500);
        }
      }
    }

    // if play is pressed while playing
    if (digitalRead(SW_PLAY) == LOW && Taudio.isPlaying()) {
      if (!isstopped) {
        pausefile();
        delay(500);
      }
    }

    // if stop button is pressed
    if (digitalRead(SW_STOP) == LOW && Taudio.isPlaying()) {
      stopplay();
      positionCounter = 0;
    }

    // change volume if stopped pressed while not playing
    if (digitalRead(SW_STOP) == LOW && !Taudio.isPlaying()) {
      toggle_volume();
    }

    // if reset combo pressed
    if (digitalRead(SW_EJECT) == LOW && digitalRead(SW_STOP) == LOW) {
      resetFunc();
    }

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

    // if menu button pressed
    if (digitalRead(SW_EJECT) == LOW && !Taudio.isPlaying()) {
      toggle_motor_controls();
    }
    // delay(200);
  }
}

// get the filecount
void getfilecount() {
  SdFile file;
  SdFile dirFile;
  if (!sd.begin(SD_CS_PIN, SD_SCK_MHZ(50))) {

    display_set(OLED_LINE_0, "Insert sd card");
    while (!sd.begin(SD_CS_PIN, SD_SCK_MHZ(50))) {
      if (digitalRead(SW_EJECT) == LOW) {
        resetFunc();
      }
    }
  }

  display_set(OLED_LINE_0, playwaymsg);

  // List files in root directory.
  if (!dirFile.open("/", O_RDONLY)) {
    sd.errorHalt("open root failed");
  }
  while (file.openNext(&dirFile, O_RDONLY)) {
    sdejected = false;
    // Skip directories and hidden files.
    if (!file.isSubDir() && !file.isHidden()) {
      filecount++;
    }
    file.close();
  }
}

// get the next filename
void getfilebatch() {
  SdFile file2;
  SdFile dirFile2;
  int dirposition = 0;
  int indposition = 0;

  if (!sd.begin(SD_CS_PIN, SD_SCK_MHZ(50))) {
    sd.initErrorHalt();
  }

  // List files in root directory.
  if (!dirFile2.open("/", O_RDONLY)) {
    sd.errorHalt("open root failed");
  }

  while (file2.openNext(&dirFile2, O_RDONLY)) {
    sdejected = false;
    // Skip directories and hidden files.
    if (!file2.isSubDir() && !file2.isHidden()) {
      if (dirposition >= fileposition) {
        if (indposition < 1) {
          memset(filename, 0, sizeof(filename)); // to zero-out the buffer
          file2.getName(filename, 100);
          filelength = strlen(filename);
        }
        indposition++;
      }
      dirposition++;
    }

    file2.close();
  }
}

// check if filename is a wav
bool isWav(char *filename) {
  int8_t len = strlen(filename);
  bool result;
  if (strstr(strlwr(filename + (len - 4)), ".wav")) {
    result = true;
  } else if (strstr(strlwr(filename + (len - 4)), ".WAV")) {
    result = true;
  } else {
    result = false;
  }

  return result;
}

// play wav file
void playwav() {
  if (isWav(filename)) {
    isstopped = false;

    display_set(OLED_LINE_0, "Playing:");
    display_set(OLED_LINE_1, filename);
    Taudio.play(filename);
    delay(1000);
    hasplayed = true;
  } else {
    set_notice("Not WAV!");
  }
}

// pause a file
void pausefile() {

  Taudio.pause();
  if (!ispaused) {
    display_set(OLED_LINE_0, "Paused!");
    ispaused = true;

  } else {
    display_set(OLED_LINE_0, "Playing:");
    display_set(OLED_LINE_1, filename);
    ispaused = false;
  }
}

// stop a file
void stopplay() {
  if (Taudio.isPlaying()) {

    Taudio.stopPlayback();
    display_set(OLED_LINE_0, "Stopped!");
    isstopped = true;
    delay(1000);
    display_set(OLED_LINE_0, playwaymsg);
  }
}

// check sd inserted
void checksd() {
  if (isstopped) {
    if (!sd.begin(SD_CS_PIN, SD_SCK_MHZ(50))) {
      filecount = 0;
      sdejected = true;

      set_notice("Card not found!");
      while (!sd.begin(SD_CS_PIN, SD_SCK_MHZ(50))) {
        if (digitalRead(SW_EJECT) == LOW && digitalRead(SW_STOP) == LOW) {
          resetFunc();
        }
      }
    }

    display_set(OLED_LINE_0, playwaymsg);
  }
}

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
void set_volume(int new_setting) {
  if (VOLUME_MAX < new_setting) {
    volume = VOLUME_MIN;
  } else {
    volume = new_setting;
  }

  //analogWrite(LED_USER, map(volume, VOLUME_MIN, VOLUME_MAX, LED_USER_MIN, LED_USER_MAX));
  analogWrite(LED_USER, LOW);
  Taudio.setVolume(volume);
}

/*
* Toggle volume settings
*/
void toggle_volume() {
  set_volume(volume + 1);

  char message[OLED_LINE_WIDTH];
  sprintf(message, "(Volume %d)", volume);
  set_notice(message);
}

/*
 * Set a notice that should be shown for a set duration and then removed from
 * the display. Note that later notices will overwrite the current one to keep
 * things responsive.
 */
void set_notice(const char *string) {
  display_set(OLED_LINE_2, string, -1);
  notice_timeout = millis() + NOTICE_DURATION;
}

/*
 * Check if the current notice has expired, clear it from the display if it has
 * already done so.
 */
void clear_notice() {
  if (notice_timeout == 0) return;
  if (notice_timeout <= millis()) {
    notice_timeout = 0;
    display_set(OLED_LINE_2);
  }
}