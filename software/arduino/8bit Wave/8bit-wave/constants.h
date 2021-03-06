#define TICK_LENGTH 250
#define SCROLL_DELAY 4 /* In ticks */
#define NOTICE_DURATION 2000
#define FILENAME_MAX_LENGTH 48

/* Player states */
#define PLAYER_IDLE 0
#define PLAYER_RUNNING 1
#define PLAYER_PAUSED 2
#define PLAYER_MOTOR_OFF 3

/* PINS */
#define LED_POWER 5
#define LED_USER 3
#define LED_NUMBER_TOTAL 2
#define REM 6
#define AUDIO_OUT 9

/* Number of physical switches (put here as a convenient way of avoiding magic
 * numbers in code). Physical pin numbers listed below.
 */
#define SW_NUMBER_TOTAL 5 
#define SW_PLAY 17
#define SW_STOP 16
#define SW_EJECT 7
#define SW_UP 14
#define SW_DOWN 15
#define SW_FLASH_FIRST
#define SW_FLASH_SECOND

/* LED Settings */
#define LED_MIN 0
#ifndef DEBUG
#define LED_MAX 56
#else
#define LED_MAX 8
#endif
#define LED_POWER_MIN 1
#define LED_POWER_MAX LED_MAX
#define LED_USER_MIN 1
#define LED_USER_MAX LED_MAX
#define LED_STEP 3
#define LED_MODE_NONE 0
#define LED_MODE_CYCLE_UP 1
#define LED_MODE_CYCLE_DOWN 2
#define LED_MODE_FADE_OUT 3
#define LED_MODE_FLASH_ON 4
#define LED_MODE_FLASH_OFF 5
#define LED_FLASH_DELAY 100

/* Display settings */
#ifdef DISPLAY_SSD1306_ASCII
#define OLED_ADDRESS 0x3C
#endif

/* Text segments used */
#define EIGHTBIT_TITLE          "    8BIT Wave   "
#define EIGHTBIT_HOMEPAGE       "github.com/tebl "
#define TEXT_PLAYING            "Playing:"
#define TEXT_PAUSED             "Paused!"
#define NOTICE_DONE             "     (done)     "
#define NOTICE_LOAD_SD          "  (loading SD)  "
#define NOTICE_MOTOR_CTRL_ON    " (MotorCtrl ON) "
#define NOTICE_MOTOR_CTRL_OFF   " (MotorCtrl OFF)"
#define NOTICE_MOTOR_ON         "   (Motor ON)   "
#define NOTICE_MOTOR_OFF        "   (Motor OFF)  "
#define ERROR_OPEN_FAILED       " (SD read error)"
#define ERROR_EMPTY_CARD        "(No files on SD)"
#define ERROR_INSERT_CARD       "(Insert SD card)"
#define ERROR_FILE_NOT_FOUND    "(file not found)"

/* CAS Player */
#ifdef PLAYER_CAS
#define EIGHTBIT_VERSION        "     CAS 0.1    "
#define TEXT_PLAY               "PLAY A CAS:"
#define TEXT_1200_BAUD          "   (1200 BAUD)  "
#define TEXT_2400_BAUD          "   (2400 BAUD)  "
#define TEXT_3600_BAUD          "   (3600 BAUD)  "

/* WAV Player */
#elif PLAYER_WAV
#define EIGHTBIT_VERSION        "     WAV 0.1    "
#define TEXT_PLAY               "PLAY A WAV:"

/* In case we forgot */
#else
#define TEXT_PLAY               "PLAY A WAV:"
#define EIGHTBIT_VERSION        "      0.1       "
#endif
