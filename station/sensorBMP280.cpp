#include <Adafruit_BMP280.h>
#include "sensorBMP280.h"
#include "settings.h"

extern "C" {
#include "user_interface.h"
}

Adafruit_BMP280 bme;

os_timer_t sensorBMP280Timer;

bool canReadSensorBMP280 = true;

void sensorBMP280Read(void *parg) {
  canReadSensorBMP280 = true;
}

void setupSensorBMP280() {
  if (!bme.begin()) {  
    Serial.println("BMP280 sensor not connected!");
  } else {
    os_timer_disarm(&sensorBMP280Timer);
    os_timer_setfn(&sensorBMP280Timer, sensorBMP280Read, NULL);
    os_timer_arm(&sensorBMP280Timer, SENSOR_BMP280_READ_INTERVAL, true);
  }
}

void loopSensorBMP280( CONN_NOTIFY_SENSOR  ) {
  if (canReadSensorBMP280) {
    canReadSensorBMP280 = false;

    float hPa = bme.readPressure() / 100;

    notify("BMP280", hPa);
  }
}
