# pragma once

/* Header Definitions */
const byte HEADER[8] = { 0x1F, 0xA6, 0xDE, 0xBA, 0xCC, 0x13, 0x7D, 0x74 };
const byte DRAGON[8] = { 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55 };
const byte ASCII[10] = { 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA };
const byte BINF[10] =  { 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0, 0xD0 };
const byte BASIC[10] = { 0xD3, 0xD3, 0xD3, 0xD3, 0xD3, 0xD3, 0xD3, 0xD3, 0xD3, 0xD3 };

#define BAUD_RATE_1200 1200
#define BAUD_RATE_2400 2400
#define BAUD_RATE_3600 3600

#define lookNothing   0     //look for nothing
#define lookHeader    1     //looking for header/data
#define lookType      2     //looking for file type
#define wHeader       3     //Write Header
#define wSilence      4     //Write Silence
#define wData         5     //Write Data
#define wClose        6     //Write closing silence

#define typeNothing   0
#define typeAscii     1
#define typeBinf      2
#define typeBasic     3
#define typeUnknown   4
#define typeEOF       5

#define SHORT_SILENCE       122
#define LONG_SILENCE        SHORT_SILENCE * 2

#define SHORT_HEADER        200
#define LONG_HEADER         800

#define buffsize      219
#define dragonBuff    4

/* Function stubs */
void initialize_cas_player();
void cas_loop();

bool cas_is_supported(const char * filename);
void cas_start(char* filename);
void cas_stop();
bool cas_pause();
bool cas_resume();
bool cas_motor_on();
bool cas_motor_off();

bool cas_is_started();
bool cas_is_running();
bool cas_is_paused();
bool cas_is_motor_off();

int cas_baud_rate();
int cas_baud_rate_up();
int cas_baud_rate_down();