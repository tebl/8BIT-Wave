#include <Arduino.h>
#include "constants.h"
#ifdef DISPLAY_SSD1306_GFX
#include <ssd1306.h>
#include <ssd1306_console.h>
#include <ssd1306_fonts.h>
#include "display.h"
#include "display_ssd1306.h"
#include "display_ssd1306_common.h"
#include "display_ssd1306_bitmap.h"
#include "typedefs.h"

extern DisplayState state;

/*
 * Displays a bitmap image on the screen, this assumes that the data should
 * take up the entire screen.
 */
void display_ssd1306_gfx_bitmap(const uint8_t *buf) {
  ssd1306_drawBitmap(0, 0, 128, 64, buf);
}
void display_ssd1306_gfx_logo() { display_ssd1306_gfx_bitmap(logo); }
void display_ssd1306_gfx_bezel() { display_ssd1306_gfx_bitmap(bezel); }

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
void display_ssd1306_gfx_update_line(const int line, int first_change = -1) {
  if (state.dirty[line]) {
    const char *ptr = (const char *) &state.lines[line];
    if (first_change > 0) ptr+=(first_change);

    ssd1306_printFixedN(
      display_ssd1306_column_to_x(first_change), 
      display_ssd1306_line_to_y(line), 
      ptr, 
      STYLE_NORMAL, 
      OLED_FACTOR);
    state.dirty[line] = false;
  }
}

/*
 * Clear the display of any contents and write back the values currently found
 * in the line buffers.
 */
void display_ssd1306_gfx_clear() {
  ssd1306_clearScreen();
  #ifndef DEBUG
    display_ssd1306_gfx_bezel();
  #endif

  for (int line = OLED_LINE_0; line < OLED_LINES; line++) {
    state.dirty[line] = true;
    display_ssd1306_gfx_update_line(line);
  }
}

/*
 * Displays the welcome screen for the firmware - given that the method of
 * displaying the welcome screen is tightly coupled to the actual attributes
 * of the screen, we'll leave this here instead of leaving it in the main
 * application.
 */
void display_ssd1306_gfx_welcome(unsigned long duration) {
  #ifndef DEBUG
    display_ssd1306_gfx_logo();
    delay(duration);
  #endif
  display_ssd1306_gfx_clear();

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
void display_ssd1306_gfx_initialize() {
  ssd1306_setFixedFont(ssd1306xled_font8x16);
  ssd1306_128x64_i2c_init();
  ssd1306_clearScreen();
  display_ssd1306_clear_all_buffers();
}
#endif