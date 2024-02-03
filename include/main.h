#include <Arduino.h>
#include "helper.h"
#include "displayHandler.hpp"
#include "sensorsHandler.hpp"
#include "graphHandler.hpp"
#include "externalStorageHandler.hpp"



#define DISPLAY_UPDATE_INTERVAL 5000
#define SENSOR_POLL_INTERVAL 5000 
#define SENSOR_LOG_INTERVAL 30000
#define DISPLAY_BRIGHTNESS 20 // Percent

const char * externStorageDirectory = "/ClimateData";
const char * externStorageDataFilePath = "/ClimateData/data.csv";


void drawPage(sensorData_t *sensData); 