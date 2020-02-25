#include <Arduino.h>
#include <ssd1306.h>
#include <ssd1306_console.h>
#include <ssd1306_fonts.h>
#include "constants.h"
#include "typedefs.h"
#include "bitmap.h"

DisplayState state;

void initialize_display() {
  ssd1306_setFixedFont(ssd1306xled_font8x16);
  ssd1306_128x64_i2c_init();
  ssd1306_fillScreen(0x00);
  ssd1306_clearScreen();
}

void display_bitmap(const uint8_t *buf) {
  ssd1306_drawBitmap(0, 0, 128, 64, buf);
}

void display_bezel() {
  display_bitmap(bezel);
}

unsigned int line_to_y(unsigned int line_number) {
  switch (line_number) {
    case 0:   return 10;
    case 1:   return 25;
    default:  return 45;
  }
}

void set_char(int line, int column, char c) {
  if (state.lines[line][column] != c) state.dirty[line] = true;
  state.lines[line][column] = c;
}

char get_char(const char *string, int position) {
  return string[position];
}

/*
 * Blank out the area of this line by painting over it with a black rectangle.
 * Not pretty, but it works so that's what you get when it's free! Should
 * probably reset colour, but any text output does it for me so a few bytes
 * spared (until it stops working).
 */
void blank_line(int line_number) {
  ssd1306_setColor(0x0000);
  ssd1306_fillRect(0, line_to_y(line_number), 128, line_to_y(line_number) + OLED_CHAR_HEIGHT);
}

/*
 * Do a line update, but for the most part try not to (overwriting with the
 * same just looks flickery).
 */
void update_line(int line) {
  if (state.dirty[line]) {
    blank_line(line);
    ssd1306_printFixedN(0, line_to_y(line), state.lines[line], STYLE_NORMAL, OLED_FACTOR);
    state.dirty[line] = false;
  }
}

void display_set(int line, const char *string, int position) {
  /* Clear line */
  if (string == nullptr) {
    for (int i = 0; i < OLED_LINE_WIDTH; i++) {
      set_char(line, i, ' ');
    }
    update_line(line);
    return;
  }

  /* Center text */
  int column = 0;
  int length = strlen(string);
  if (length < OLED_LINE_WIDTH) {
    if (position == -1 && length < OLED_LINE_WIDTH) {
      for (int i = 0; i < (OLED_LINE_WIDTH - length) / 2; i++) {
        set_char(line, column, ' ');
        column++;
      }
    }
  }

  /* Output string */
  if (length < OLED_LINE_WIDTH) {
    /* Outout (or already centered) string */
    for (int i = 0; i < OLED_LINE_WIDTH; i++) {
      if (0 <= position);
      set_char(line, column, get_char(string, i));
      column++;

      if (OLED_LINE_WIDTH < column) break;
    }
  } else {
    /* Scroll string */
    int char_pos = position;
    for (; column < OLED_LINE_WIDTH; column++) {
      char c = get_char(string, char_pos);

      if (c == 0) {
        set_char(line, column, ' ');
        char_pos = 0;
      } else {
        set_char(line, column, c);
        char_pos++;
      }
    }
  }
  set_char(line, OLED_LINE_WIDTH, 0);
  update_line(line);
}

void display_set(int line, const __FlashStringHelper *string) {
  const char *ptr = (const char *) string;
  for (int i = 0; i < OLED_LINE_WIDTH; i++) {
    char c = pgm_read_byte_near(ptr++);
    
    set_char(line, i, c);
    if (c == 0) break;
  }
  set_char(line, OLED_LINE_WIDTH, 0);
  update_line(line);
}

void display_clock(int line, const int hours, const int minutes, const int seconds) {
  sprintf(state.lines[line], "    %02d:%02d:%02d   ", hours, minutes, seconds);
  state.dirty[line] = true;
  update_line(line);
}

void display_clear() {
  ssd1306_clearScreen();
  display_bezel();

  for (int line = OLED_LINE_0; line < OLED_LINES; line++) {
    memset(state.lines[line], 0, OLED_LINE_WIDTH + 1);
    display_set(line, nullptr, 0);
  }
}

void display_welcome(unsigned long duration) {
  display_bitmap(logo);
  delay(duration);
  display_clear();

  display_set(OLED_LINE_0, F(EIGHTBIT_TITLE));
  display_set(OLED_LINE_1, F(EIGHTBIT_VERSION));
  delay(2000);
}