#ifndef _TYPEDEFS_H
#define _TYPEDEFS_H

typedef struct {
    void (*short_press)();
    void (*long_press)();
} SwitchCallback;

typedef struct {
    SwitchCallback functions[SW_NUMBER_TOTAL];
} SwitchFunctions;

typedef struct {
    const int pin_number;
    const int min;
    const int max;
    int mode;
    int value;
    int parameter;
} LedSetting;

typedef struct {
    char lines[OLED_LINES][OLED_LINE_WIDTH + 1];
    bool dirty[OLED_LINES];
} DisplayState;

#endif