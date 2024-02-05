#include "MQTTtasks.hpp"
#include "sensorsHandler.hpp"


uint8_t mqttHandler_init(int port, MQTT_RX_DATA* mqttData);


void mqttHandler_transmit_readings(sensorData_t* sensorData);