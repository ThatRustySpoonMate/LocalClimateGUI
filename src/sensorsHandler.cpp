#include "sensorsHandler.hpp"

Adafruit_AHTX0 aht;

TwoWire *AHT20Bus = new TwoWire(1);



uint8_t climateSensor_init() {
    AHT20Bus->setPins(27, 22); // SDA: 27, SCL: 22

    AHT20Bus->begin();

    if (!aht.begin(AHT20Bus)) {
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