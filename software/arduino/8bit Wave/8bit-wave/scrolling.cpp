#include <Arduino.h>
#include <TMRpcm.h>
#include "constants.h"
#include "display.h"

extern char filename[FILENAME_MAX_LENGTH];
extern TMRpcm Taudio;

int scroll_length = 0;
int scroll_index = 0;

/*
 * Handles scrolling the filename across line 1 of the display, but in note that
 * in order to keep things moving at a sort of acceptable speed we'll need manual
 * sync every time the filename changes.
 */
void scroll_filename() {
  if (!Taudio.isPlaying()) {
    display_set(OLED_LINE_1, filename, scroll_index);
    if (scroll_index < scroll_length) scroll_index++;
    else scroll_index = 0;
  }
}

/*
 * Notifies the scrolling mechanism that the data has changed, so we should
 * probably start at the beginning again.
 */
void scroll_sync() {
  scroll_length = strlen(filename);
  scroll_index = 0;
}
