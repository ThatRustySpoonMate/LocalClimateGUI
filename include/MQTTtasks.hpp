#include "WifiHandler.hpp"
#include <PubSubClient.h>


typedef struct {
    uint8_t mqtt_enabled : 1;
    uint8_t mqtt_connected : 1;
} MQTTStatus_t;

void setup_mqtt(const char *MQTT_BROKER_IP, const int MQTT_BROKER_PORT, const char *DEV_NAME, const char *RX_TEMP, const char *RX_HUM, const char *RX_PRES, const char *MANAGEMENT_TOPIC);

void mqtt_transmit(const char *topic, const char *payload);

void mqtt_keep_alive();

uint8_t mqtt_connect();

void mqtt_reconnect();

void message_rx_callback(char* topic, byte* message, unsigned int length);

void mqtt_disconnect();

