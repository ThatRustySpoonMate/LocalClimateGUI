#include <Arduino.h>
#include "helper.h"
#include "displayHandler.hpp"
#include "sensorsHandler.hpp"
#include "graphHandler.hpp"
#include "externalStorageHandler.hpp"
#include "credentials.h"
#include "MQTTHandler.hpp"



#define DISPLAY_UPDATE_INTERVAL 5000 // Millis
#define SENSOR_POLL_INTERVAL 5000    // Millis
#define SENSOR_LOG_INTERVAL 30000    // Millis
#define MQTT_SENSOR_TRANSMIT_INTERVAL 30000 // Millis
#define DISPLAY_BRIGHTNESS 20        // Percent
#define WIFI_CONNECT_TIMEOUT 15 * 1000 // Millis


const char *MQTT_TOPIC_TX_TEMPERATURE = "home/upstairs/living-room/display/temperature";
const char *MQTT_TOPIC_TX_HUMIDITY = "home/upstairs/living-room/display/humidity";
const char *MQTT_TOPIC_RX_TEMPERATURE = "home/outside/garden/temperature";
const char *MQTT_TOPIC_RX_HUMIDITY = "home/outside/garden/humidity";
const char *MQTT_TOPIC_RX_PRESSURE = "home/outside/garden/pressure";
const char *MQTT_MANAGEMENT_TOPIC = "manage/upstairs/living-room/display";


const char * externStorageDirectory = "/ClimateData";
const char * externStorageDataFilePath = "/ClimateData/data.csv";


void drawPage(sensorData_t *sensData); 

void config();