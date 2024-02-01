#include "displayHandler.hpp"

static TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

uint16_t displayOnTime, displayOffTime;

void displayHandler_init(uint8_t brightness) {// Brightness is a value between 1-100
  tft.init();
  tft.setRotation(2); // Portrait mode
  tft.fillScreen(TFT_WHITE);
  tft.setTextColor(TFT_BLACK);
  tft.setTextFont(4);

  displayOnTime = brightness;
  displayOffTime = 100 - displayOnTime;
  
  return;
}

void displayHandler_draw_text_at_pos(int32_t posX, int32_t posY, const String& string, uint8_t size) {

    tft.setTextSize(size);

    tft.drawString(string, posX, posY);

    return;
}


void displayHandler_set_bg_colour(uint32_t col) {
    tft.fillScreen(col);

    return;
}

void displayHander_clear(void) {
    tft.fillScreen(TFT_WHITE);

    return;
}



void displayHandler_PWM(void * parameter) {
    for(;;) {
        digitalWrite(TFT_BL, LOW);

        delayMicroseconds(displayOffTime);

        digitalWrite(TFT_BL, HIGH);

        delayMicroseconds(displayOnTime);
    }
}