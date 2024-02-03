#include <Arduino.h>
#include "helper.h"
#include "displayHandler.hpp"
#include "sensorsHandler.hpp"
#include "graphHandler.hpp"



#define DISPLAY_UPDATE_INTERVAL 5000
#define SENSOR_POLL_INTERVAL 5000 
#define DISPLAY_BRIGHTNESS 20 // Percent

void drawPage(sensorData_t *sensData);