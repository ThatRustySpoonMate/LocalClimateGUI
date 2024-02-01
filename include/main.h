#include <Arduino.h>
#include "helper.h"
#include "displayHandler.hpp"
#include "sensorHandler.hpp"


#define displayUpdateInterval 1000
#define sensorPollInterval 5000 

void drawPage();