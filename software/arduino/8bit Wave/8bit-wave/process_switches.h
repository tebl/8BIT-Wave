void initialize_switches();
void set_callback(int pin_number, void (*short_press)() = nullptr, void (*long_press)() = nullptr);
void process_switches();