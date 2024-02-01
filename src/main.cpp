#include "main.h"

TaskHandle_t DisplayPWMTask;
displayInput_t dispIn;
sensorData_t sensorData;
Graph temperatureGraph = Graph(220, 80, 15000);


uint16_t posx, posy;
uint8_t touched = 0;


void setup() {
  setCpuFrequencyMhz(80);

  Serial.begin(115200);

  // Init display
  displayHandler_init(&dispIn, 20);

  // Init AHT20 sensor
  if(!climateSensor_init()) {
    displayHandler_set_text_colour(0x0000fff); // Red
    displayHandler_draw_text_at_pos(0, 0, "Unable to find AHT20", 2);
    displayHandler_set_text_colour(TFT_BLACK); // Restore text colour
    displayHandler_draw_text_at_pos(0, 12, "--------------------------------", 2);
    displayHandler_draw_text_at_pos(0, 25, "Check top connector", 2);
    displayHandler_draw_text_at_pos(0, 50, "on right hand side", 2);
    displayHandler_draw_text_at_pos(0, 75, "of device and", 2);
    displayHandler_draw_text_at_pos(0, 100, "restart", 2);
    for(;;)delay(1000);
  } else {
    displayHandler_draw_text_at_pos(0, 0, "Display: ", 1);
    displayHandler_draw_text_at_pos(0, 15, "AHT20 Sensor: ", 1);
    displayHandler_set_text_colour(0xfff000); // Blue - GG-BB-RR

    displayHandler_draw_text_at_pos(55, 0, "Connected", 1);
    displayHandler_draw_text_at_pos(85, 15, "Connected", 1);

    displayHandler_set_text_colour(TFT_BLACK); // Restore text colour
    displayHandler_draw_text_at_pos(0, 30, "Starting Application...", 1);
  }

  temperatureGraph.trackVariable(&(sensorData.temperature));


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

  temperatureGraph.runDataCollector();

}


void drawPage(sensorData_t *sensData) {

  displayHander_clear();

  displayHandler_draw_T_divider(displayHandler_get_height() / 3);

  // Inside data

  displayHandler_draw_text_at_pos(18, 110, "Inside", 2);

  displayHandler_draw_line(21, 130, 86, 130, TFT_BLACK);

  displayHandler_draw_text_at_pos(0,155, String(sensData->temperature) + "c", 2);

  displayHandler_draw_text_at_pos(0,196, String(sensData->humidity) + "%", 2);

  displayHandler_set_text_colour(0xfff000); // Blue

  displayHandler_draw_text_at_pos(0,140, "Temperature", 1);

  displayHandler_draw_text_at_pos(0,181, "Humidity", 1);

  displayHandler_set_text_colour(TFT_BLACK); // Restore text colour


  // Outside data

  displayHandler_draw_text_at_pos(displayHandler_get_width()/2 +18, 110, "Outside", 2);

  displayHandler_draw_line(displayHandler_get_width()/2 +18, 130, displayHandler_get_width()/2 +98, 130, TFT_BLACK);

  displayHandler_draw_text_at_pos(displayHandler_get_width()/2 +2, 155, "Coming soon", 2);

  displayHandler_draw_text_at_pos(displayHandler_get_width()/2 +2, 195, "Coming soon", 2);

  displayHandler_draw_text_at_pos(displayHandler_get_width()/2 +2, 235, "Coming soon", 2);

  displayHandler_set_text_colour(0xfff000); // Blue

  displayHandler_draw_text_at_pos(displayHandler_get_width()/2 +2, 140, "Temperature", 1);

  displayHandler_draw_text_at_pos(displayHandler_get_width()/2 +2, 180, "Humidity", 1);

  displayHandler_draw_text_at_pos(displayHandler_get_width()/2 +2, 220, "Pressure", 1);

  displayHandler_set_text_colour(TFT_BLACK); // Restore text colour


  // Graph

  displayHandler_draw_text_at_pos(0, 0, "Temperature past 30 mins", 1);

  

  return;
}

