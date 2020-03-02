#pragma once
void initialize_commands();
void configure_switches(int player_state);

void press_play();
void press_stop();
void press_up();
void press_down();

void check_audio_finished();
void toggle_motor_controls();

#ifdef PLAYER_WAV
void increase_volume();
void decrease_volume();
#endif

#ifdef PLAYER_CAS
void baud_rate_up();
void baud_rate_down();
#endif