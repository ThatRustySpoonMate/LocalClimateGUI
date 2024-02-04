#include "main.h"

TaskHandle_t DisplayPWMTask;
displayInput_t dispIn;
sensorData_t sensorData;
Graph* temperatureGraph = nullptr;
Graph* humidityGraph = nullptr;
externStorage_t sdCardStatus;


uint16_t posx, posy;
uint8_t touched = 0;


void setup() {
  setCpuFrequencyMhz(80);

  Serial.begin(115200);

  // Init display
  displayHandler_init(&dispIn, DISPLAY_BRIGHTNESS);

  // Init Graph
  temperatureGraph = new Graph(210, 106, displayHandler_get_width(), 2, 0x000fff, 60000);
  humidityGraph = new Graph(210, 106, displayHandler_get_width(), 1, 0xfff000, 6000);

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
  }


  // Init SD Card
  displayHandler_draw_text_at_pos(0, 30, "SD Card: ", 1);
  if(!SD.begin(5)){
    // Unable to detect SD Card
    Serial.println("Card Mount Failed");
    displayHandler_set_text_colour(TFT_BLUE); // Yellow
    displayHandler_draw_text_at_pos(55, 30, "Not detected ", 1);
    sdCardStatus.connected = false;
    sdCardStatus.used = false;
  } else {
    // SD Card successfully init'd
    uint8_t cardType = SD.cardType();
    displayHandler_set_text_colour(0xfff000); // Blue
    displayHandler_draw_text_at_pos(55, 30, "Connected", 1);
    sdCardStatus.connected = true;
    sdCardStatus.used = true;

   // Setup SD Card file structure
   // If already exists, won't overwrite
    createDir(SD, externStorageDirectory);
  }
  displayHandler_set_text_colour(TFT_BLACK); // Restore text colour


  // Setup graph to track var
  temperatureGraph->trackVariable(&(sensorData.temperature));
  humidityGraph->trackVariable(&(sensorData.humidity));


  // Initilize PWM task
  xTaskCreatePinnedToCore(
      displayHandler_PWM, /* Function to implement the task */
      "hdl_pwm", /* Name of the task */
      5000,  /* Stack size in words */
      NULL,  /* Task input parameter */
      0,  /* Priority of the task */
      &DisplayPWMTask,  /* Task handle. */
      0); /* Core where the task should run */


  // Final GUI Text
  displayHandler_set_text_colour(TFT_BLACK); // Restore text colour
  displayHandler_draw_text_at_pos(0, 45, "Starting Application...", 1);

}

void loop() {
  static uint32_t displayTimer, sensorTimer, sensorLogTimer;

  if(every_n_ms(SENSOR_POLL_INTERVAL, &sensorTimer)) {
    climateSensor_poll(&sensorData);
  }

  if(every_n_ms(DISPLAY_UPDATE_INTERVAL, &displayTimer)) {
    drawPage(&sensorData);
  }

  if(sdCardStatus.used == true && every_n_ms(SENSOR_LOG_INTERVAL, &sensorLogTimer)) {
    writeReadingToStorage(SD, &sensorData);
  }

  temperatureGraph->runDataCollector();
  humidityGraph->runDataCollector();

}


void drawPage(sensorData_t *sensData) {

  // Clear screen
  displayHander_clear();

  // Draw Graph

  displayHandler_draw_text_at_pos(0, 0, "Temperature past 70 mins", 1);

  displayHandler_draw_graph(temperatureGraph);

  displayHandler_draw_graph(humidityGraph);

  // Draw 'T' Divider

  displayHandler_draw_T_divider(displayHandler_get_height() / 3);

  // Inside data

  displayHandler_draw_text_at_pos(18, 110, "Inside", 2);

  displayHandler_draw_line(21, 130, 86, 130, TFT_BLACK);

  displayHandler_draw_text_at_pos(0,155, String(sensData->temperature) + "c", 3);

  displayHandler_draw_text_at_pos(0,196, String(sensData->humidity) + "%", 3);

  displayHandler_set_text_colour(0xfff000); // Blue

  displayHandler_draw_text_at_pos(0,140, "Temperature", 1);

  displayHandler_draw_text_at_pos(0,181, "Humidity", 1);

  displayHandler_set_text_colour(TFT_BLACK); // Restore text colour


  // Outside data

  displayHandler_draw_text_at_pos(displayHandler_get_width()/2 +18, 110, "Outside", 2);

  displayHandler_draw_line(displayHandler_get_width()/2 +18, 130, displayHandler_get_width()/2 +98, 130, TFT_BLACK);

  displayHandler_draw_text_at_pos(displayHandler_get_width()/2 +2, 155, "Coming soon", 3);

  displayHandler_draw_text_at_pos(displayHandler_get_width()/2 +2, 195, "Coming soon", 3);

  displayHandler_draw_text_at_pos(displayHandler_get_width()/2 +2, 235, "Coming soon", 3);

  displayHandler_set_text_colour(0xfff000); // Blue

  displayHandler_draw_text_at_pos(displayHandler_get_width()/2 +2, 140, "Temperature", 1);

  displayHandler_draw_text_at_pos(displayHandler_get_width()/2 +2, 180, "Humidity", 1);

  displayHandler_draw_text_at_pos(displayHandler_get_width()/2 +2, 220, "Pressure", 1);

  displayHandler_set_text_colour(TFT_BLACK); // Restore text colour

  

  return;
}

