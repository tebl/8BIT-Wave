void initialize_led();
void led_tick();
void set_led_neutral(int pin_number);
void set_led_flash(int pin_number, int value = -1);
void set_led_cycle(int pin_number);
void set_led_fade_out(int pin_number, int value = -1, int tick_delay = 0);
int second_to_ticks(int num_seconds);
void flash_led_now(int pin_number, int num_flashes);