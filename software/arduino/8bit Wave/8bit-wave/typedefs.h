#pragma once

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