#include "displayHandler.hpp"

static TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h
displayInput_t *displayInput;

uint16_t displayOnTime, displayOffTime;

void displayHandler_init(displayInput_t *display_input, uint8_t brightness) {// Brightness is a value between 1-100
  tft.init();
  tft.setRotation(2); // Portrait mode
  tft.fillScreen(TFT_WHITE);
  tft.setTextColor(TFT_BLACK);
  tft.setTextFont(1);

  displayOnTime = brightness;
  displayOffTime = 100 - displayOnTime;

  displayInput = display_input;
  
  return;
}


void displayHandler_draw_text_at_pos(int32_t posX, int32_t posY, const String& string, uint8_t size) {

    tft.setTextSize(size);

    tft.drawString(string, posX, posY);

    return;
}


// Draws a 'T' divider with the top of the 'T' given by Y Pos arg, top of the 'T' extends to the edges of the screen in the X-axis and the stalk of the 'T' extends to the bottom of the screen in the Y-axis
void displayHandler_draw_T_divider(uint16_t ypos) {
    tft.drawLine(0, ypos, tft.width(), ypos, TFT_BLACK);
    tft.drawLine(tft.width()/2, ypos, tft.width()/2, tft.height(), TFT_BLACK);

    return;
}

void displayHandler_draw_line(uint32_t xs, uint32_t ys, uint32_t xe, uint32_t ye, uint32_t col) {
    tft.drawLine(xs, ys, xe, ye, col);

    return;
}


void displayHandler_set_bg_colour(uint32_t col) {
    tft.fillScreen(col);

    return;
}

void displayHandler_set_text_colour(uint32_t col){
    tft.setTextColor(col);

    return;
}


uint32_t displayHandler_get_width() {
    return tft.width();
}


uint32_t displayHandler_get_height() {
    return tft.height();
}   


void displayHander_clear(void) {
    tft.fillScreen(TFT_WHITE);

    return;
}


uint8_t displayHander_get_touch(uint16_t *posx, uint16_t *posy){

    uint8_t touched;

    touched = tft.getTouchRaw(posx, posy);

    return touched;
}


// Handle PWMMING of display to achieve target brightness
// As well as brighten screen for x seconds when touched 
void displayHandler_PWM(void * parameter) {

    for(;;) {

        // > x seconds since last screen touch
        digitalWrite(TFT_BL, LOW);

        delayMicroseconds(displayOffTime);

        digitalWrite(TFT_BL, HIGH);

        delayMicroseconds(displayOnTime);
    
    }
}