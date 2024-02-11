#ifndef __MQTT_H__
#define __MQTT_H__

#include "commandHandler.h"

#if ENABLE_WIFI_AND_MQTT == 1

#include "WiFi.h"
#include <PubSubClient.h>

void init_mqtt(void);
bool connectMQTT();
bool checkMQTTconnection();
void reconnectMQTT();
void disconnectMQTT();
bool publishMQTTMessage(const char *topic, const char *payload);
bool subscribeMQTTEvent(const char *topic);
bool unsubscribeMQTTEvent(const char *topic);
void onMQTTEvent(const char topic[], byte *payload, unsigned int length);
#endif

#endif /*__MQTT_H__*/
