#include <WiFi.h>


typedef struct {
    uint8_t wifi_enabled : 1;
    uint8_t wifi_connected : 1;
} WifiStatus_t;

uint8_t setup_wifi(const char *ssid, const char *password, uint32_t timeout);

void wifi_disconnect();