#pragma once

#include <Arduino.h>
#include <PubSubClient.h>

#define CONN_NOTIFY void (*notify)(String, float)

class Conn {
  public:
    Conn(String stationID);
    void loop();
    void notify(String sensor, float value);
    void notify(String topic, String payload, bool retained = false);
    void listen(String topic);
  private:
    String _stationID;
    PubSubClient* _PubSubClient;
    void connect();
    String fullTopic(String topic);
};

