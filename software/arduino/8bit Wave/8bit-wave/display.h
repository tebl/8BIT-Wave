void initialize_display();
void display_welcome(unsigned long duration = 2000);
void display_clear();
void display_set(const int line);
void display_set(const int line, const char *string, const int position = 0);
void display_set(const int line, const __FlashStringHelper *string);
void display_clock(const int line, const int hours, const int minutes, const int seconds);