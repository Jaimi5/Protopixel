#include "esp_log.h"

#include "mqtt_led_bridge.h"

#include "config.h"
#include "services/mqtt_service.h"
#include "drivers/led_driver.h"

static const char* TAG = "MQTT_LED_BRIDGE";

void mqtt_led_bridge_init(void) {
    // Subscribe to the MQTT topic where commands for the LED will be published
    mqtt_service_subscribe(MQTT_TOPIC_LED);
}

void mqtt_led_callback(const char* topic, const char* message) {
    if (strcmp(topic, MQTT_TOPIC_LED) != 0) {
        ESP_LOGW(TAG, "Received MQTT message on topic %s, but this is not the LED topic", topic);
        return;
    }

    ESP_LOGI(TAG, "Received MQTT message on topic %s: %s", topic, message);

    if (strcmp(message, "ON") == 0)
        set_led_state(true);
    else if (strcmp(message, "OFF") == 0)
        set_led_state(false);
    else {
        ESP_LOGW(TAG, "Unknown command: %s", message);
    }
    
}
