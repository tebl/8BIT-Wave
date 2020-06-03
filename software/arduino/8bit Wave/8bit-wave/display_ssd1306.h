#ifdef DISPLAY_SSD1306_ASCII
  #define update_line display_ssd1306_ascii_update_line
#endif

#ifdef DISPLAY_SSD1306_GFX
  #define update_line display_ssd1306_gfx_update_line
#endif

void update_line(const int line, int first_change);