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

void displayHandler_set_bg_colour(uint32_t col);

void displayHander_clear(void);

uint8_t displayHander_get_touch(uint16_t *posx, uint16_t *posy);

void displayHandler_PWM(void * parameter);

