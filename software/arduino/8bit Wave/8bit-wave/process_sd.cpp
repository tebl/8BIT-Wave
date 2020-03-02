#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "SdFat.h"
#include "constants.h"
#include "display.h"
#include "scrolling.h"
#include "notice.h"
#include "player.h"
extern char filename[FILENAME_MAX_LENGTH];
const uint8_t SD_CS_PIN = SS;

SdFat sd;
SdFile entry;

bool sd_dirty = true;
int file_index = 0;

/*
 * Given a previously known file index, attempts to step through the
 * directory contents on the SD card root. The routine will either stop when
 * we encounter the end of the directory or we've counted up until the we get
 * to the file that we want.
 */
void get_sd_position() {
  SdFile root;
  
  if (!root.open("/", O_RDONLY)) {
    set_notice(F(ERROR_OPEN_FAILED));
    sd.errorHalt(F("open root failed"));
    delay(2000);
    return;
  }

  int counted = -1;
  while (entry.openNext(&root, O_RDONLY)) {
    if (!entry.isSubDir() && !entry.isHidden()) {
      memset(filename, 0, sizeof(filename));
      if (entry.getName(filename, FILENAME_MAX_LENGTH)) {
        if (player_is_supported(filename)) {
          if (counted == -1) counted = 0;
          else counted++;
        }
      }
    }

    entry.close();
    if (file_index == counted) break;
  }
  if (counted < file_index) file_index = counted;

  if (file_index != -1) {
    scroll_reset();
    display_filename(OLED_LINE_1, filename);
  } else {
    display_set(OLED_LINE_1);
    set_notice(F(ERROR_EMPTY_CARD));
    delay(2000);
  }
}

/*
 * Ensures that the SD card has been inserted, will block indefinitely until we
 * actually detect the card - this is done before any other processing if
 * needed.
 */
bool check_sd_inserted() {
  while(!sd.begin(SD_CS_PIN, SD_SCK_MHZ(50))) {
    set_notice(F(ERROR_INSERT_CARD));
    delay(1000);
  }
  return true;
}

/*
 * Called by main program, takes care of handling tasks related to SD-card.
 */
bool process_sd() {
  if (sd_dirty) {
    check_sd_inserted();
    get_sd_position();
    sd_dirty = false;
    return true;
  }
  return false;
}

bool is_file_selected() {
    return file_index == -1;
}

void next_file() {
  file_index++;
  sd_dirty = true;
}

void previous_file() {
    if (file_index > 0) {
        file_index--;
    }
    sd_dirty = true;
}
