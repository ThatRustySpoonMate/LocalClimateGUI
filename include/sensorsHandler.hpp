#include <Adafruit_Sensor.h>
#include <Adafruit_AHTX0.h>


typedef struct {
    float temperature;
    float humidity;
} sensorData_t;


uint8_t climateSensor_init();

void climateSensor_poll(sensorData_t *sensData);
