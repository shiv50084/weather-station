#include <Esp.h>
#include "settings.h"
#include "conn.h"
#include "alarm.h"
#include "sensorDHT.h"

Conn* conn;
char stationID[10];

void setup() {
  Serial.begin(115200);

  sprintf(stationID, "%d", ESP.getChipId());
  
  setupAlarm();
  conn = new Conn(stationID);

  setupSensorDHT();
}

void loop() {
  conn->loop();
  
  loopSensorDHT([](const char* sensor, float value) {
    conn->notify(sensor, value);  
  });
}

