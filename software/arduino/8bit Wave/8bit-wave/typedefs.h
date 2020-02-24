#ifndef _TYPEDEFS_H
#define _TYPEDEFS_H

typedef struct {
    void (*short_press)();
    void (*long_press)();
} WaveState;

typedef struct {
    char lines[OLED_LINES][OLED_LINE_WIDTH + 1];
    bool dirty[OLED_LINES];
} DisplayState;

#endif