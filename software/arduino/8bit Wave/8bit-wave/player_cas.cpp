#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "SdFat.h"
#include "TimerOne.h"
#include "constants.h"
#include "player_cas.h"

extern SdFile entry;
extern SdFat sd;

extern volatile byte player_state;

unsigned long bytesRead = 0;
byte dragonMode = 0;
byte out = LOW;
byte input[11];
volatile byte wbuffer[buffsize + 1][2];
volatile byte morebuff = HIGH;

/* From header */
int baud_rate = BAUD_RATE_1200;
int scale = 1;
int period = 208;

byte currentTask=lookHeader;
byte currentType=typeNothing;
byte fileStage=0;

byte copybuff = LOW;
byte btemppos = 0;
byte bits[11];

/* Dragon 32/64 CAS processing */
byte lastByte;
volatile long count = 0;


/* Used by audio out */
volatile byte pass = 0;
volatile byte pos = 0;
volatile byte working = 0;

/*
 * Check if the extension of the filename currently specified matches that of
 * a wav-file.
 */
bool cas_is_supported(const char * filename) {
  const size_t length = strlen(filename);
  if (length < 5) return false;
  if (!(filename[length - 4] == '.')) return false;
  if (!(filename[length - 3] == 'c' || filename[length - 3] == 'C')) return false;
  if (!(filename[length - 2] == 'a' || filename[length - 2] == 'A')) return false;
  if (!(filename[length - 1] == 's' || filename[length - 1] == 'S')) return false;
  return true;
}

/* 
 * Check if the player is currently running, this does not count any of the
 * paused states as running. If we are running, we'll check if the player
 * stopped since we last checked it before returning. There's a race-condition
 * here, but without a dedicated resume function it's as close as we get.
 */
bool cas_is_running() {
  return player_state == PLAYER_RUNNING;
}

/*
 * Check wether the player has been actively stopped by the user and not by any
 * other means (player stopped by itself or paused by REM).
 */
bool cas_is_paused() {
  return player_state == PLAYER_PAUSED;
}

/*
 * Pause the player if possible, returns wether the player is actually paused at
 * the end - this is done to ensure that the states haven't changed for any other
 * reason such as either no longer playing or paused by REM(ote). 
 */
bool cas_pause() {
  if (cas_is_running()) {
    noInterrupts();
    player_state = PLAYER_PAUSED;
    interrupts();
  }
  return cas_is_paused();
}

/*
 * Resume playing the file if possible, but note that this may not be possible if
 * the player had been paused by REM(ote) or some other unforseen thing happening
 * along the way.
 */
bool cas_resume() {
  if (cas_is_paused()) {
    noInterrupts();
    player_state = PLAYER_RUNNING;
    interrupts();
  }
  return !cas_is_paused();
}

/*
 * Check wether the player has been started, but note that it may have been
 * paused by the user or via REM(ote).
 */
bool cas_is_started() {
  switch (player_state) {
    case PLAYER_IDLE:
      return false;
    case PLAYER_RUNNING:
      return cas_is_running();
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
bool cas_is_motor_off() {
  return player_state == PLAYER_MOTOR_OFF;
}

/*
 * Turn off the player with the REM(ote) being the source, this also ensures
 * that the user can no longer resume the tape by himself and in this way 
 * allow the tape to get ahead of the program.
 */
bool cas_motor_off() {
  if (cas_is_running()) {
    noInterrupts();
    player_state = PLAYER_MOTOR_OFF;
    interrupts();
  }
  return cas_is_motor_off();
}

/*
 * Resume playing when previously paused via REM(ote).
 */
bool cas_motor_on() {
  if (cas_is_motor_off()) {
    noInterrupts();
    player_state = PLAYER_RUNNING;
    interrupts();
  }
  return cas_motor_off();
}

int readfile(byte bytes, unsigned long p) {
  int i = 0;
  if (entry.seekSet(p)) {
    i = entry.read(input, bytes);
  } 
  return i;
}

void clearBuffer() {
  for (int i = 0; i<= buffsize; i++) {
    wbuffer[i][0] = 2;
    wbuffer[i][1] = 2;
  }
}

/*
 * Start the player
 */
void cas_start(char* filename) {
  if(!entry.open(filename,O_READ)) return;
  byte r = 0;

  out = LOW;
  if((r = readfile(8, bytesRead)) == 8) {
    if(!memcmp(input, DRAGON, 8)) {
      out = HIGH;
      dragonMode = 1;
      period = 240;
      Timer1.setPeriod(period);
      Timer1.stop();
    }
  }

  bytesRead = 0;
  currentType = typeNothing;
  currentTask = lookHeader;
  fileStage = 0;

  //noInterrupts();
  clearBuffer();
  player_state = PLAYER_RUNNING;
  //interrupts();
  Timer1.restart();
}

/*
 * Should ensure that the player stopped, or at least as close as we are able
 * to get before returning. We are using is_started here just in case the
 * player has been paused, either directly or via motor REM(ote).
 */
void cas_stop() {
  if (cas_is_started()) {
    Timer1.stop();
    entry.close();
    bytesRead = 0;
    dragonMode = 0;
  }
  player_state = PLAYER_IDLE;
}

/*
 * Write a byte into the buffers.
 */
void cas_write(byte b) {
  if (dragonMode == 1) {
    for (int i = 0; i < 8; i++) {
      if(b & 1) {
        bits[i] = 1;
      } else bits[i] = 0;
      b = b >> 1;
    }
    bits[8] = 2;
    bits[9] = 2;
    bits[10] = 2;
  } else {
    bits[0] = 0;
    for (int i=1; i < 9; i++) {
      if(b & 1) {
        bits[i] = 1;
      } else bits[i] = 0;
      b = b >> 1;
    }

    bits[9] = 1;
    bits[10] = 1;
  }
}

void cas_silence() {
  for(int i=0;i<11;i++) {
    bits[i] = 2;
  }
}

void cas_header() {
  for(int i = 0; i < 11; i++) {
    bits[i] = 1;
  }
}

/*
 * Process CAS data specifically created for the Dragon32/64 computer.
 */
void process_dragon() {
  lastByte = input[0];
  byte r = 0;
  if ((r = readfile(1, bytesRead)) == 1) {
    currentTask = wData;
    cas_write(input[0]);
    bytesRead += 1;
  } else {
    if (currentTask == wData) {
      if (lastByte != 0x55) { 
        cas_write(0x55);
      }

      count = 54;
      currentTask = wSilence;
    }

    if (currentTask == wSilence) {      
      if (!count == 0) {
        cas_silence();
        count--;
      } else {
        cas_stop();
      }
    }
  }
}

/*
 * Process CAS file data.
 */
void process_cas() {
  byte r=0;
  if (currentType == typeEOF) {
    if(!count==0) {
      cas_silence();
      count+=-1;  
    } else cas_stop();    
    return;
  }

  if (currentTask == lookHeader || currentTask == wData) {
    if ((r=readfile(8,bytesRead)) == 8) {
      if (!memcmp(input, HEADER, 8)) {
        if (fileStage == 0) {
          currentTask = lookType;
        } else {
          currentTask = wSilence;
          count = SHORT_SILENCE * scale;
        }
        
        if (currentType == typeNothing) fileStage = 1;
        bytesRead += 8;
      }
    } else {
      if (r == 0) {
        currentType = typeEOF;
        currentTask = wClose;
        count = LONG_SILENCE * scale;
      }
    }
  }

  if (currentTask == lookType) {
    if ((r = readfile(10, bytesRead)) == 10) {
      if (!memcmp(input, ASCII, 10)) {
        currentType = typeAscii;
        currentTask = wSilence;
        count = LONG_SILENCE * scale;
        fileStage = 1;
      } else if (!memcmp(input, BINF, 10)) {
        currentType = typeBinf;
        currentTask  = wSilence;
        count = LONG_SILENCE*scale;
        fileStage = 1;
      } else if (!memcmp(input, BASIC, 10)) {
        currentType = typeBasic;
        currentTask = wSilence;
        count = LONG_SILENCE * scale;
        fileStage = 1;
      } else {
        currentType = typeUnknown;
        currentTask = wSilence;
        count = LONG_SILENCE * scale;
        fileStage = 1;       
      }
    } else {
      currentType = typeUnknown;
      currentTask = wSilence;
      count = LONG_SILENCE * scale;
      fileStage = 1;       
    }
  }

  if (currentTask == wSilence) {
    if (!count == 0) {
      cas_silence();
      count += -1;
    } else {
      currentTask = wHeader;
      if (fileStage == 1) {
        count = LONG_HEADER * scale;
        fileStage += 1;
      } else {
        count = SHORT_HEADER * scale;
        if (currentType == typeAscii) {
          fileStage += 1;
        } else {
          fileStage = 0;
        }
      }
    }
   }

   if (currentTask == wHeader) {
    if (!count == 0) {
      cas_header();
      count +=- 1;
    } else {
      currentTask = wData;
      return;
    }
  }

  if (currentTask == wData) {
    cas_write(input[0]);
    if (input[0] == 0x1a && currentType == typeAscii) {
      fileStage = 0;
    }
   }

   if (currentTask == lookHeader || currentTask == lookType || currentTask == wData) {
    bytesRead += 1;
   } 
}

/*
 * Called from the main execution loop, and - if the player is running - takes
 * care of buffering data for playback. This is mostly unchanged from the
 * standard CASduino, for the most part I've just removed the parts dealing with
 * the user interface.
 */
void cas_loop() {
  if (!cas_is_running()) return;

  noInterrupts();
  copybuff = morebuff;
  morebuff = LOW;
  interrupts();

  if (copybuff == HIGH) {
    btemppos = 0;
    copybuff = LOW;
  }
  if (btemppos <= buffsize - (dragonBuff * dragonMode)) { 
    if (dragonMode == 1 ) {
      process_dragon();

      noInterrupts();
      for (int t = 0; t < 8; t++) {
        if (btemppos <= buffsize) {
          wbuffer[btemppos][working ^ 1] = bits[t];
          interrupts();
          btemppos+=1;         
        } 
      }

      //interrupts();
    } else {
      process_cas();

      noInterrupts();
      for(int t=0;t<11;t++) {
        if (btemppos <= buffsize) {
          wbuffer[btemppos][working ^ 1] = bits[t];
          interrupts();
          btemppos += 1;
        }
      }
      //interrupts();
    }
  }
}

void wave() {
  digitalWrite(LED_USER, HIGH);
  return;
  if (cas_is_running()) {
    switch (wbuffer[pos][working]) {
      case 0:
        if ((pass == 0) | (pass == 1)) {
          digitalWrite(AUDIO_OUT, out);
        } else {
          digitalWrite(AUDIO_OUT, !out);
        }
        break;

      case 1:
        if ((pass == 0) | (pass == 2)) {
          digitalWrite(AUDIO_OUT, out);
        } else {
          digitalWrite(AUDIO_OUT, !out);
        }
        if (dragonMode == 1 && pass == 1) {
          pass = 3;
        }
        break;

      case 2:
        digitalWrite(AUDIO_OUT, LOW);
        break;
    }
  
    pass = pass + 1;
    if (pass == 4) {
      pass = 0;
      pos += 1;
      if (pos > buffsize - (dragonBuff * dragonMode)) {
        pos = 0;
        working ^=1;
        morebuff = HIGH;
      }
    }
  } else digitalWrite(AUDIO_OUT, LOW);
}

int cas_baud_rate(int new_baud_rate) {
  if (new_baud_rate < BAUD_RATE_1200) new_baud_rate = BAUD_RATE_1200;
  if (new_baud_rate > BAUD_RATE_3600) new_baud_rate = BAUD_RATE_3600;
  baud_rate = new_baud_rate;

  scale = baud_rate / 1200;
  period = 208 / scale;

  return baud_rate;
}

int cas_baud_rate() {
  return baud_rate;
}

int cas_baud_rate_up() {
  switch (baud_rate) {
    default:
    case BAUD_RATE_1200: return cas_baud_rate(BAUD_RATE_2400);
    case BAUD_RATE_2400: return cas_baud_rate(BAUD_RATE_3600);
    case BAUD_RATE_3600: return cas_baud_rate();
  }
}

int cas_baud_rate_down() {
  switch (baud_rate) {
    default:
    case BAUD_RATE_1200: return cas_baud_rate();
    case BAUD_RATE_2400: return cas_baud_rate(BAUD_RATE_1200);
    case BAUD_RATE_3600: return cas_baud_rate(BAUD_RATE_2400);
  }
}

void initialize_cas_player() {
  clearBuffer();
  pinMode(AUDIO_OUT, OUTPUT);
  digitalWrite(AUDIO_OUT, LOW);

  player_state = PLAYER_IDLE;

  cas_baud_rate(BAUD_RATE_1200);
  Timer1.initialize(period);
  Timer1.attachInterrupt(wave);
  Timer1.stop();
}