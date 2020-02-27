void initialize_player();

bool player_is_supported(const char * filename);
void player_start(char* filename);
void player_stop();
bool player_pause();
bool player_resume();
void player_motor_on();
void player_motor_off();

bool player_is_started();
bool player_is_running();
bool player_is_paused();
bool player_is_motor_off();

int player_volume();
int player_volume_up();
int player_volume_down();