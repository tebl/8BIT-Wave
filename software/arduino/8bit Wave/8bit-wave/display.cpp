#include <Arduino.h>
#include <ssd1306.h>
#include <ssd1306_console.h>
#include <ssd1306_fonts.h>
#include "constants.h"
#include "typedefs.h"
#include "bitmap.h"

DisplayState state;

/* 
 * Clears the buffer set aside specifically for scratching data onto before
 * flipping them onto the screen later. Note that using OLED_LINE_WIDTH in
 * the second statement is not a type, we've set aside an extra byte for the
 * NULL-character.
 */
void clear_buffer() {
  memset(state.buffer, ' ', OLED_LINE_WIDTH);
  state.buffer[OLED_LINE_WIDTH] = 0;
}

/* 
 * Clears line buffers as well as display buffer. Also, see comment for
 * clear_buffer about the last line (not a bug).
 */
void clear_all_buffers() {
  clear_buffer();

  for (int line = OLED_LINE_0; line < OLED_LINES; line++) {
    memset(state.lines[line], ' ', OLED_LINE_WIDTH);
    state.lines[line][OLED_LINE_WIDTH] = 0;
    state.dirty[line] = true;
  }
}

/*
 * Initialize OLED display along with associated buffers, should be called
 * from the setup function of the firmware.
 */
void initialize_display() {
  ssd1306_setFixedFont(ssd1306xled_font8x16);
  ssd1306_128x64_i2c_init();
  ssd1306_clearScreen();
  clear_all_buffers();
}

/*
 * Translates line numbers to OLED y-coordinates. At the moment we assume a
 * fixed font size of 8x16 pixels so we need to ensure that everything fits
 * within those boundaries.
 */
unsigned int line_to_y(const unsigned int line_number) {
  switch (line_number) {
    case 0:   return 10;
    case 1:   return 26;
    default:  return 42;
  }
}

/*
 * Translate column number to OLED x-coordinates. At the moment we assume a
 * fixed font size of 8x16 though that's not likely to change anytime soon.
 */
int column_to_x(const int column) {
  if (column == -1) return 0;
  return (column * OLED_CHAR_WIDTH);
}

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
void update_line(const int line, int first_change = -1) {
  if (state.dirty[line]) {
    const char *ptr = (const char *) &state.lines[line];
    if (first_change > 0) ptr+=(first_change);

    ssd1306_printFixedN(column_to_x(first_change), line_to_y(line), ptr, STYLE_NORMAL, OLED_FACTOR);
    state.dirty[line] = false;
  }
}

/*
 * Get character at the specified position from the buffer, but note that
 * depending on previous usage this may contain old data.
 */
char get_buffer_char(const int column) {
  return state.buffer[column];
}

/*
 * Set a character in the buffer.
 */
void set_buffer_char(const int column, const char c) {
  state.buffer[column] = c;
}

/*
 * Set line column specified to character, value returned designates wether
 * we've detected a change in contents.
 */
bool set_char(const int line, const int column, const char c) {
  if (state.lines[line][column] != c) state.dirty[line] = true;
  state.lines[line][column] = c;
  return state.dirty[line];
}

/*
 * Get a specific character number from the supplied string.
 */
char get_char(const char *string, int position) {
  return string[position];
}

/*
 * Flip the buffer into the screen (double-buffering technique), but when going
 * through the data we'll do so in the oppisite direction in order to obtain
 * the last changed position for update_line.
 */
void flip_buffer_to(const int line) {
  int first_change = OLED_LINE_WIDTH;

  for (int i = (OLED_LINE_WIDTH - 1); i >= 0; i--) {
    if (set_char(line, i, get_buffer_char(i)) && i < first_change) {
      first_change = i;
    }
  }

  update_line(line, first_change);
}

/*
 * Given the pointer to a string, we'll copy the characters into the buffer.
 * After the end of the string has been reached, we'll pad out the data with
 * spaces in order to have something the display can display directly. 
 */
void display_set_buffer(const char *ptr) {
  bool end_found = false;
  for (int i = 0; i < OLED_LINE_WIDTH; i++) {
    if (!end_found) {
      char c = pgm_read_byte_near(ptr++);
      
      if (c == 0) end_found = true;
      else set_buffer_char(i, c);
    }

    if (end_found) set_buffer_char(i, ' ');
  }
  set_buffer_char(OLED_LINE_WIDTH, 0);
}

/*
 * The same as above, except here we use a string that originates in Flash
 * memory instead of RAM.
 */
void display_set_buffer(const __FlashStringHelper *string) {  
  display_set_buffer((const char *) string);
}

/*
 * Displays a bitmap image on the screen, this assumes that the data should
 * take up the entire screen.
 */
void display_bitmap(const uint8_t *buf) {
  ssd1306_drawBitmap(0, 0, 128, 64, buf);
}
void display_logo() { display_bitmap(logo); }
void display_bezel() { display_bitmap(bezel); }

/*
 * Clears the specified line.
 */
void display_set(const int line) {
  clear_buffer();
  flip_buffer_to(line);
}

/*
 * Display a string on the specified line. Position can be used in order to
 * have the routine scroll through the data, in which case we'll wrap around
 * characters in order to fill the space available.
 * 
 * A position of -1 means that we should attempt to center the line on screen
 * (not available when the string is longer than the available space). When
 * filter_extension is set we remove the four characters of the string,
 * assuming it to be a three character file extension.
 */
int display_set(const int line, const char *string, const int position, bool filter_extension) {
  int length = strlen(string);
  int actual_length = length;
  if (filter_extension) actual_length = length - 4;

  if (actual_length <= OLED_LINE_WIDTH) {
    int column = 0;

    /* Position -1 means that we are supposed to center the text on the line
     * instead of outputting it at the start.
     */
    if (position == -1 && length < OLED_LINE_WIDTH) {
      for (int i = 0; i < (OLED_LINE_WIDTH - length) / 2; i++) {
        set_buffer_char(column, ' ');
        column++;
      }
    }

    /* Outout string at the current position */
    bool end_found = false;
    for (int i = 0; i < OLED_LINE_WIDTH; i++) {
      char c = get_char(string, i);
      if (c == 0) end_found = true;
      if (filter_extension && (actual_length <= i)) end_found = true;

      if (end_found) set_buffer_char(column, ' ');
      else set_buffer_char(column, c);

      /* Increase column position, but ensure that we don't go past the actual
       * display area. */
      column++;
      if (OLED_LINE_WIDTH < column) break;
    }
  } else {
    /* Scroll string */
    int char_pos = position % (length + 1);
    for (int column; column < OLED_LINE_WIDTH; column++) {
      char c = get_char(string, char_pos);

      if (c == 0) {
        set_buffer_char(column, ' ');
        char_pos = 0;
      } else if (filter_extension && ((length - 4) <= char_pos)) {
        set_buffer_char(column, ' ');
        char_pos++;
      } else {
        set_buffer_char(column, c);
        char_pos++;
      }
    }
  }

  flip_buffer_to(line);

  /* Return the next possible position for scrolling */
  if (position < 0) return position;
  if (position < length) return position + 1;
  return 0;
}

/*
 * The same as the above, except that we default to blanking out the four
 * character file extension (we'll just put spaces instead, calling the
 * whole thing a feature instead of a hack).
 */
int display_filename(const int line, const char *string, const int position = 0, bool filter_extension = true) {
  return display_set(line, string, position, filter_extension);
}

/*
 * Serves the same function as above, but we're using a string found in ROM
 * instead of RAM. Instead of using cycles to process the string in any way
 * using RAM, we'll just assume that it's formatted the way it should be
 * displayed (meaning we'll waste ROM bytes on spaces instead of doing
 * things like scroll or center text).
 */
void display_set(const int line, const __FlashStringHelper *string) {
  display_set_buffer(string);
  flip_buffer_to(line);
}

/*
 * Displays a clock on the specified line. Note that any values will have to
 * be provided elsewhere as we're just outputting things here (instead of
 * attributing meaning to them at this point).
 */
void display_clock(const int line, const int hours, const int minutes, const int seconds) {
  sprintf(state.buffer, "    %02d:%02d:%02d   ", hours, minutes, seconds);
  flip_buffer_to(line);
}

/*
 * Clear the display of any contents and write back the values currently found
 * in the line buffers.
 */
void display_clear() {
  ssd1306_clearScreen();
  #ifndef DEBUG
  display_bezel();
  #endif

  for (int line = OLED_LINE_0; line < OLED_LINES; line++) {
    state.dirty[line] = true;
    update_line(line);
  }
}

/*
 * Displays the welcome screen for the firmware - given that the method of
 * displaying the welcome screen is tightly coupled to the actual attributes
 * of the screen, we'll leave this here instead of leaving it in the main
 * application.
 */
void display_welcome(unsigned long duration) {
  #ifndef DEBUG
  display_logo();
  delay(duration);
  #endif
  display_clear();

  #ifndef DEBUG
  display_set(OLED_LINE_0, F(EIGHTBIT_TITLE));
  display_set(OLED_LINE_1, F(EIGHTBIT_VERSION));
  display_set(OLED_LINE_2, F(EIGHTBIT_HOMEPAGE));
  delay(2000);
  #endif
}