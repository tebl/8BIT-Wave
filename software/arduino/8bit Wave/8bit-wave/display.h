#pragma once

#ifdef DISPLAY_SSD1306_ASCII
  #define DISPLAY_FAMILY_SSD1306

  #define initialize_display display_ssd1306_ascii_initialize
  #define display_clear display_ssd1306_ascii_clear
  #define display_welcome display_ssd1306_ascii_welcome
#endif

#ifdef DISPLAY_SSD1306_GFX
  #define DISPLAY_FAMILY_SSD1306
  #define OLED_FACTOR 0

  #define initialize_display display_ssd1306_gfx_initialize
  #define display_clear display_ssd1306_gfx_clear
  #define display_welcome display_ssd1306_gfx_welcome
#endif

#ifdef DISPLAY_FAMILY_SSD1306
  #define OLED_LINE_0 0
  #define OLED_LINE_1 1
  #define OLED_LINE_2 2
  #define OLED_LINES 3
  #define OLED_LINE_WIDTH 16
  #define OLED_CHAR_HEIGHT 8
  #define OLED_CHAR_WIDTH 16

  typedef struct {
      char lines[OLED_LINES][OLED_LINE_WIDTH + 1];
      bool dirty[OLED_LINES];
      char buffer[OLED_LINE_WIDTH + 1];
  } DisplayState;

  #define display_set display_ssd1306_set
  #define display_filename display_ssd1306_filename
  #define display_clock display_ssd1306_clock
#endif

void initialize_display();
void display_welcome(unsigned long duration = 2000);
void display_clear();
void display_set(const int line);
int display_set(const int line, const char *string, const int position = 0, bool filter_extension = false);
int display_filename(const int line, const char *string, const int position = 0, bool filter_extension = true);
void display_set(const int line, const __FlashStringHelper *string);
void display_clock(const int line, const int hours, const int minutes, const int seconds);