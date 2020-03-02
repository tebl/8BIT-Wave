void initialize_tzx_player();

bool player_tzx_is_supported(const char * filename);
void player_tzx_start(char* filename);
void player_tzx_stop();
bool player_tzx_pause();
bool player_tzx_resume();
void player_tzx_motor_on();
void player_tzx_motor_off();

bool player_tzx_is_started();
bool player_tzx_is_running();
bool player_tzx_is_paused();
bool player_tzx_is_motor_off();

int player_tzx_volume();
int player_tzx_volume_up();
int player_tzx_volume_down();