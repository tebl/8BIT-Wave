void initialize_display();
void display_welcome(unsigned long duration = 2000);
void display_set(int line, const char *string = nullptr, int position = 0);
void display_set(int line, const __FlashStringHelper *string);
