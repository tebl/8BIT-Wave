#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "SdFat.h"
#include "constants.h"
#include "display.h"
#include "scrolling.h"
#include "notice.h"
extern char filename[FILENAME_MAX_LENGTH];
const uint8_t SD_CS_PIN = SS;

SdFat sd;

bool sd_dirty = true;
int file_index = 0;

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
void get_sd_position() {
  SdFile a_file;
  SdFile root;
  
  if (!root.open("/", O_RDONLY)) {
    set_notice("(SD read error)");
    sd.errorHalt("open root failed");
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
