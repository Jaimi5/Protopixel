#pragma once

#include "esp_event.h"

// Initialize the bridge between MQTT and LED server
void mqtt_led_bridge_init(void);

// Callback function for handling MQTT messages related to the LED
void mqtt_led_callback(const char* topic, const char* message);