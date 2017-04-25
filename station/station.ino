#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "ssid";
const char* password = "password";

const char* mqtt_server = "mqtt_server";

char stationID[10];

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void setup() {
  Serial.begin(115200);
  
  sprintf(stationID, "%d", ESP.getChipId());

  setup_wifi();

  client.setServer(mqtt_server, 1883);
  mqtt_connect();
}

void setup_wifi() {
  Serial.printf("\nConnecting station %s to SSID %s", stationID, ssid);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Ok.");
  
  Serial.printf("IP address: %s\n", WiFi.localIP().toString().c_str());
}

void mqtt_connect() {
  while (!client.connected()) {
    Serial.printf("Attempting MQTT connection on %s...", mqtt_server);
    if (client.connect(stationID)) {
      Serial.println(" Ok.");

      // Once connected, publish an announcement...
      char msg[100];
      sprintf(msg, "station/%s/status", stationID);
      client.publish(msg, "on");
    } else {
      Serial.printf(" error: %s. Trying again in 10 seconds.\n", client.state());
      delay(10000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    mqtt_connect();
  }
  client.loop();
}

