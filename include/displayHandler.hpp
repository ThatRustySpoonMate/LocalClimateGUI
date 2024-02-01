#pragma once

#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library

#define DISPLAY_LIGHT_ON_TOUCH_DURATION 10000 // MS


typedef struct {

    uint16_t posX;
    uint16_t posY;
    uint32_t inputTime;

} displayInput_t;


void displayHandler_init(displayInput_t *display_input, uint8_t brightness);

void displayHandler_draw_text_at_pos(int32_t posX, int32_t posY, const String& string, uint8_t size);

void displayHandler_draw_T_divider(uint16_t ypos);

void displayHandler_draw_line(uint32_t xs, uint32_t ys, uint32_t xe, uint32_t ye, uint32_t col);

void displayHandler_set_bg_colour(uint32_t col);

void displayHandler_set_text_colour(uint32_t col);

uint32_t displayHandler_get_width();

uint32_t displayHandler_get_height();

void displayHander_clear(void);

uint8_t displayHander_get_touch(uint16_t *posx, uint16_t *posy);

void displayHandler_PWM(void * parameter);

