#include "MQTTtasks.hpp"

WiFiClient espClient;
PubSubClient client(espClient);

const char *BROKER_IP;
int BROKER_PORT;
const char *DEVICE_NAME;
const char *RX_TOPICS[4];

void setup_mqtt(const char *MQTT_BROKER_IP, const int MQTT_BROKER_PORT, const char *DEV_NAME, const char *RX_TEMP, const char *RX_HUM, const char *RX_PRES, const char *MANAGEMENT_TOPIC) {
  BROKER_IP = MQTT_BROKER_IP;
  BROKER_PORT = MQTT_BROKER_PORT;
  DEVICE_NAME = DEV_NAME;
  RX_TOPICS[0] = RX_TEMP;
  RX_TOPICS[1] = RX_HUM;
  RX_TOPICS[2] = RX_PRES;
  RX_TOPICS[3] = MANAGEMENT_TOPIC;

  client.setServer(BROKER_IP, BROKER_PORT);

  client.setCallback(message_rx_callback);

  return;
}


void mqtt_transmit(const char *topic, const char *payload) {
  mqtt_keep_alive();
  client.publish(topic, payload);

  return;
}


void mqtt_keep_alive() {
  if (!client.connected()) {
    mqtt_reconnect();
  }

  client.loop();

  return;
}

// Try to connect once if not already connected
uint8_t mqtt_connect() {
  if(!client.connected()) {
    if (client.connect(DEVICE_NAME)) {
      client.subscribe(RX_TOPICS[0]);
      client.subscribe(RX_TOPICS[1]);
      client.subscribe(RX_TOPICS[2]);
      client.subscribe(RX_TOPICS[3]);
      return true;
    } else {
      return false;
    }
  }

  return true;
}

// If we are not already connected, repeatedly connect until we are connected - blocking
void mqtt_reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(DEVICE_NAME)) {
      Serial.println("connected");
      // Subscribe
      client.subscribe(RX_TOPICS[0]);
      client.subscribe(RX_TOPICS[1]);
      client.subscribe(RX_TOPICS[2]);
      client.subscribe(RX_TOPICS[3]);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }

  return;
}

void message_rx_callback(char* topic, byte* message, unsigned int length) {
  String messageTemp;

  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");

  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    
    messageTemp += (char)message[i];
  }
  Serial.println();
  
  

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off". 
  // Changes the output state according to the message
  // if (String(topic) == RX_TOPIC) {
  //   Serial.print("Changing output to ");
  //   if(messageTemp == "on"){
  //     Serial.println("on");
  //   }
  //   else if(messageTemp == "off"){
  //     Serial.println("off");
  //   }
  // }

  return;
}


void mqtt_disconnect() {
  client.disconnect();
  
  return;
}


