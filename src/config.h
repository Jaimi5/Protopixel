#pragma once

// Define the device type and comment the other
#define LAMP 
// #define CONTROLLER

// LED related pins
#define LED_PIN GPIO_NUM_8

// Button related pins
#define BUTTON_PIN GPIO_NUM_27

// Debounce time in microseconds
#define DEBOUNCE_TIME 200000 // 200ms

// WiFi Configuration
#define WIFI_SSID      "Jan-Protopixel"
#define WIFI_PASS      "protopixel"
#define WIFI_MAXIMUM_RETRY  5

// MQTT Configuration
#define MQTT_BROKER_IP      "192.168.1.117"
#define MQTT_PORT      "1883"
#define MQTT_USERNAME  ""
#define MQTT_PASSWORD  ""

#if defined(LAMP)
#define MQTT_CLIENT_ID "esp32-lamp"

#elif defined(CONTROLLER)
#define MQTT_CLIENT_ID "esp32-controller"
#endif

#define MQTT_TOPIC_LED     "led"

#if !defined(LAMP) && !defined(CONTROLLER)
#error "You must define LAMP or CONTROLLER"
#endif

#if defined(LAMP) && defined(CONTROLLER)
#error "You must define only one of LAMP or CONTROLLER"
#endif