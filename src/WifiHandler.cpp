#include "WifiHandler.hpp"



uint8_t setup_wifi(const char *WIFI_SSID, const char *WIFI_PASSWORD, uint32_t WIFI_CONNECT_TIMEOUT) {
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  //  Start timeout counter
  uint32_t wifi_start_timestamp = millis();
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");

    if(millis() - wifi_start_timestamp > WIFI_CONNECT_TIMEOUT) {
      // Timeout has elapsed
      WiFi.disconnect();
      return false;
    }
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  return true;
}

void wifi_disconnect() {
  WiFi.disconnect();

  return;
}


void wifi_keep_alive(const char *WIFI_SSID, const char *WIFI_PASSWORD) {
  if(WiFi.status() != WL_CONNECTED) {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  }

  return;
}
