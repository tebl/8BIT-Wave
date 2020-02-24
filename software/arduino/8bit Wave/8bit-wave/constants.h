#define EIGHTBIT_TITLE "8bit Wave"
#define EIGHTBIT_VERSION "0.1"

#define TICK_LENGTH 250
#define NOTICE_DURATION 1000
#define FILENAME_MAX_LENGTH 100
#define VOLUME_MIN 0
#define VOLUME_MAX 7

/* PINS */
#define LED_POWER 5
#define LED_USER 3
#define LED_NUMBER_TOTAL 2
#define REM 6

/* Number of physical switches (put here as a convenient way of avoiding magic
 * numbers in code). Physical pin numbers listed below.
 */
#define SW_NUMBER_TOTAL 5 
#define SW_PLAY 17
#define SW_STOP 16
#define SW_EJECT 7
#define SW_UP 14
#define SW_DOWN 15
//#define SW_FLASH_FIRST
#define SW_FLASH_SECOND

/* LED Settings */
#define LED_MIN 0
#define LED_MAX 56
#define LED_POWER_MIN LED_MIN
#define LED_POWER_MAX LED_MAX
#define LED_USER_MIN LED_MIN
#define LED_USER_MAX LED_MAX
#define LED_STEP 3
#define LED_MODE_NONE 0
#define LED_MODE_CYCLE_UP 1
#define LED_MODE_CYCLE_DOWN 2
#define LED_MODE_FADE_OUT 3
#define LED_MODE_FLASH_ON 4
#define LED_MODE_FLASH_OFF 5
#define LED_FLASH_DELAY 100

#define OLED_FACTOR 0
#define OLED_LINE_0 0
#define OLED_LINE_1 1
#define OLED_LINE_2 2
#define OLED_LINES 3
#define OLED_LINE_WIDTH 16