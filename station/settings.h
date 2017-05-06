#pragma once

#include <Arduino.h>

#define WIFI_SSID "ssid"
#define WIFI_PASSWORD "password"

#define MQTT_SERVER "mqtt_server"
#define MQTT_PORT 1883

#define ALARM_LED_PIN D4

#define SENSOR_DHT_PIN D1
#define SENSOR_DHT_READ_INTERVAL 60000
#define SENSOR_DHTTYPE DHT11

#define SENSOR_ULTRASONIC_TRIGGER_PIN D7
#define SENSOR_ULTRASONIC_ECHO_PIN D8
#define SENSOR_ULTRASONIC_READ_INTERVAL 1000

