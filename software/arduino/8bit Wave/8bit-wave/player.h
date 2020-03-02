#ifdef PLAYER_CAS
#define initialize_player initialize_cas_player
#define player_loop cas_loop
#define player_is_supported cas_is_supported
#define player_start cas_start
#define player_stop cas_stop
#define player_pause cas_pause
#define player_resume cas_resume
#define player_motor_on cas_motor_on
#define player_motor_off cas_motor_off
#define player_is_started cas_is_started
#define player_is_running cas_is_running
#define player_is_paused cas_is_paused
#define player_is_motor_off cas_is_motor_off

int cas_baud_rate();
int cas_baud_rate_up();
int cas_baud_rate_down();
#endif

#ifdef PLAYER_WAV
#define initialize_player initialize_wav_player
#define player_loop wav_loop
#define player_is_supported wav_is_supported
#define player_start wav_start
#define player_stop wav_stop
#define player_pause wav_pause
#define player_resume wav_resume
#define player_motor_on wav_motor_on
#define player_motor_off wav_motor_off
#define player_is_started wav_is_started
#define player_is_running wav_is_running
#define player_is_paused wav_is_paused
#define player_is_motor_off wav_is_motor_off

int wav_volume();
int wav_volume_up();
int wav_volume_down();
#endif

void initialize_player();
void player_loop();

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