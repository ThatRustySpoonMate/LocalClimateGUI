#include "main.h"

TaskHandle_t DisplayPWMTask;
displayInput_t dispIn;
sensorData_t sensorData;


uint16_t posx, posy;
uint8_t touched = 0;


void setup() {
  setCpuFrequencyMhz(80);

  Serial.begin(115200);

  // Init display
  displayHandler_init(&dispIn, 25);

  // Init AHT20 sensor
  if(!climateSensor_init()) {
    displayHandler_set_text_colour(0x0000fff); // Red
    displayHandler_draw_text_at_pos(0, 0, "Unable to find AHT20", 1);
    displayHandler_set_text_colour(TFT_BLACK); // Restore text colour
    displayHandler_draw_text_at_pos(0, 10, "--------------------------------", 1);
    displayHandler_draw_text_at_pos(0, 25, "Check top connector", 1);
    displayHandler_draw_text_at_pos(0, 50, "on right hand side of", 1);
    displayHandler_draw_text_at_pos(0, 75, "device", 1);
    for(;;)delay(1000);
  }

  // Initilize PWM task
  xTaskCreatePinnedToCore(
      displayHandler_PWM, /* Function to implement the task */
      "hdl_pwm", /* Name of the task */
      5000,  /* Stack size in words */
      NULL,  /* Task input parameter */
      0,  /* Priority of the task */
      &DisplayPWMTask,  /* Task handle. */
      0); /* Core where the task should run */


}

void loop() {
  static uint32_t displayTimer, sensorTimer;

  if(every_n_ms(sensorPollInterval, &sensorTimer)) {
    climateSensor_poll(&sensorData);
  }

  if(every_n_ms(displayUpdateInterval, &displayTimer)) {
    drawPage(&sensorData);
  }

}


void drawPage(sensorData_t *sensData) {

  displayHander_clear();

  displayHandler_draw_text_at_pos(0,50, String(sensData->temperature) + "c", 2);

  displayHandler_draw_text_at_pos(0,100, String(sensData->humidity) + "%", 2);

  return;
}

