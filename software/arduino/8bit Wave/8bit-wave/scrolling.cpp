#include <Arduino.h>
#include "constants.h"
#include "display.h"
#include "player.h"

extern char filename[FILENAME_MAX_LENGTH];
extern int file_index;
int scroll_length = 0;
int scroll_index = 0;

/*
 * Handles scrolling the filename across line 1 of the display, but do note that
 * in order to keep things moving at a sort of acceptable speed we'll need manual
 * sync every time the filename changes.
 */
void scroll_filename() {
  if (!player_is_started() && file_index >= 0) {
    scroll_index = display_filename(OLED_LINE_1, filename, scroll_index);
  }
}

/*
 * Notifies the scrolling mechanism that the data has changed, so we should
 * probably start all the way back at the beginning again.
 */
void scroll_reset() {
  scroll_length = strlen(filename);
  scroll_index = 0;
}
