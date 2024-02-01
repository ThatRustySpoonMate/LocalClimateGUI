#include <Arduino.h>
#include "helper.h"
#include "displayHandler.hpp"
#include "sensorsHandler.hpp"



#define displayUpdateInterval 5000
#define sensorPollInterval 5000 

void drawPage(sensorData_t *sensData);