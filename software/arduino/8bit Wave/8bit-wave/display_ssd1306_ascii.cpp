#include <Arduino.h>
#include "constants.h"
#ifdef DISPLAY_SSD1306_ASCII
#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include "display.h"
#include "display_ssd1306.h"
#include "display_ssd1306_common.h"
#include "typedefs.h"

SSD1306AsciiWire oled;
extern DisplayState state;

/*
 * Do a line update, but for the most part try not to do so (overwriting with
 * the same data just ends up looking flickery). The library used with the
 * OLED display blanks out the entire block taken allocated to the character,
 * so we don't have to worry about characters appearing on top of each other.
 * 
 * Could probably have set the default value of first_change to 0 instead of
 * -1, but for readability I wanted to separate the actual character position
 * from the fact of not knowing where it is.  
 */
void display_ssd1306_ascii_update_line(const int line, int first_change = -1) {
  if (state.dirty[line]) {
    const char *ptr = (const char *) &state.lines[line];
    if (first_change > 0) ptr+=(first_change);

    oled.setRow((line + 1) * 2);
    oled.clearToEOL();
    oled.println(state.lines[line]);
    state.dirty[line] = false;
  }
}

/*
 * Clear the display of any contents and write back the values currently found
 * in the line buffers.
 */
void display_ssd1306_ascii_clear() {
  oled.clear();

  for (int line = OLED_LINE_0; line < OLED_LINES; line++) {
    state.dirty[line] = true;
    display_ssd1306_ascii_update_line(line);
  }
}

/*
 * Displays the welcome screen for the firmware - given that the method of
 * displaying the welcome screen is tightly coupled to the actual attributes
 * of the screen, we'll leave this here instead of leaving it in the main
 * application.
 */
void display_ssd1306_ascii_welcome(unsigned long duration) {
  display_ssd1306_ascii_clear();

  #ifndef DEBUG
    display_set(OLED_LINE_0, F(EIGHTBIT_TITLE));
    display_set(OLED_LINE_1, F(EIGHTBIT_VERSION));
    display_set(OLED_LINE_2, F(EIGHTBIT_HOMEPAGE));
    delay(2000);
  #endif
}

/*
 * Initialize OLED display along with associated buffers, should be called
 * from the setup function of the firmware.
 */
void display_ssd1306_ascii_initialize() {
  Wire.begin();
  Wire.setClock(400000L);
  oled.begin(&Adafruit128x64, OLED_ADDRESS);
  oled.setFont(X11fixed7x14);
  oled.clear();
  oled.setScrollMode(SCROLL_MODE_OFF);
  display_ssd1306_clear_all_buffers();
}
#endif