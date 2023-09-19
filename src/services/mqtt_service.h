#pragma once

#include "esp_event.h"

#include "mqtt_client.h"

void mqtt_service_init();
void mqtt_service_subscribe(const char* topic);
void mqtt_service_send(const char* topic, const char* data, int len);