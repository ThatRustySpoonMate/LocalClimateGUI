#include "sensorsHandler.hpp"

Adafruit_AHTX0 aht;

uint8_t climateSensor_init() {


    if (!aht.begin()) {
        Serial.println("Could not find AHT? Check wiring");
        return 0;
    }

    return 1;

}


void climateSensor_poll(sensorData_t *sensData) {
    sensors_event_t humidity, temp;

    aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
    sensData->temperature = temp.temperature;
    sensData->humidity = humidity.relative_humidity;

    return;
} 