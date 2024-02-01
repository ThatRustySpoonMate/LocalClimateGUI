#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library

void displayHandler_init(uint8_t brightness);

void displayHandler_draw_text_at_pos(int32_t posX, int32_t posY, const String& string, uint8_t size);

void displayHandler_set_bg_colour(uint32_t col);

void displayHander_clear(void);

void displayHandler_PWM(void * parameter);

