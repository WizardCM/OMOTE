#ifndef __MQTT_H__
#define __MQTT_H__

#include "commandHandler.h"

#ifdef ENABLE_WIFI_AND_MQTT

#include "WiFi.h"
#include <PubSubClient.h>

void init_mqtt(void);
bool checkMQTTconnection();
bool publishMQTTMessage(const char *topic, const char *payload);
void disconnectMQTT();
bool subscribeMQTTEvent(const char *topic);
bool unsubscribeMQTTEvent(const char *topic);
void onMQTTEvent(const char topic[], byte *payload, unsigned int length);
#endif

#endif /*__MQTT_H__*/
