#include <Arduino.h>
#include "constants.h"

#ifdef PLAYER_CAS
#include "player_cas.h"
#elif PLAYER_WAV
#include "player_wav.h"
#endif

volatile byte player_state = PLAYER_IDLE;