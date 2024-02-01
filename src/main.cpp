#include "main.h"

TaskHandle_t DisplayPWMTask;


void setup() {
  setCpuFrequencyMhz(80);

  Serial.begin(115200);

  displayHandler_init(25);


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
  static uint32_t displayTimer;

  if(every_n_ms(displayUpdateInterval, &displayTimer)) {
    drawPage();
  }

}



void drawPage() {
  displayHander_clear();

  displayHandler_draw_text_at_pos(0,50, "27c", 3);

  displayHandler_draw_text_at_pos(0,100, "35%", 3);



}

