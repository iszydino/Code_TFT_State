#ifndef _MQTT_H_
#define _MQTT_H_

#include <stdint.h>
#include <stdlib.h>

#include <WiFi.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>


#define MQTT_SERVER     "broker.emqx.io"
#define MQTT_PORT       1883
#define MQTT_TOPIC      "demo_fan"

void Wifi_Setup(void);
void MQTT_Setup(void);
void MQTT_Publish(uint8_t state);

#endif
