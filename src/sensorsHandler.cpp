#include "sensorsHandler.hpp"

Adafruit_AHTX0 aht;

TwoWire *test = new TwoWire(1);



uint8_t climateSensor_init() {
    test->setPins(27, 22);

    test->begin();

    if (!aht.begin(test)) {
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