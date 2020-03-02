void initialize_wav_player();

bool wav_is_supported(const char * filename);
void wav_start(char* filename);
void wav_stop();
bool wav_pause();
bool wav_resume();
void wav_motor_on();
void wav_motor_off();

bool wav_is_started();
bool wav_is_running();
bool wav_is_paused();
bool wav_is_motor_off();

int wav_volume();
int wav_volume_up();
int wav_volume_down();