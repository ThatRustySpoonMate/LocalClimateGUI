#include "MQTThandler.hpp"


extern const char* MQTT_BROKER_IP;
//extern const int MQTT_BROKER_PORT;
extern const char* DEVICE_ID;
extern const char* MQTT_TOPIC_RX_TEMPERATURE;
extern const char* MQTT_TOPIC_RX_HUMIDITY;
extern const char* MQTT_TOPIC_RX_PRESSURE;
extern const char* MQTT_MANAGEMENT_TOPIC;
extern const char* MQTT_TOPIC_TX_TEMPERATURE;
extern const char* MQTT_TOPIC_TX_HUMIDITY;

uint8_t mqttHandler_init(int port) {
    setup_mqtt(MQTT_BROKER_IP, port, DEVICE_ID, MQTT_TOPIC_RX_TEMPERATURE, MQTT_TOPIC_RX_HUMIDITY, MQTT_TOPIC_RX_PRESSURE, MQTT_MANAGEMENT_TOPIC);
    return mqtt_connect();
}


void mqttHandler_transmit_readings(sensorData_t* sensorData) {

  mqtt_transmit(MQTT_TOPIC_TX_TEMPERATURE, String(sensorData->temperature).c_str() );
  mqtt_transmit(MQTT_TOPIC_TX_HUMIDITY, String(sensorData->humidity).c_str() );

  return;
}