#include "esp_log.h"
#include "tasks/led_task.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_event.h"

#include "drivers/button_driver.h"
#include "drivers/led_driver.h"
#include "services/wifi_service.h"
#include "services/mqtt_service.h"
#include "bridge/mqtt_led_bridge.h"

QueueHandle_t gpio_evt_queue = NULL;

static const char* TAG = "main";

void app_main(void) {
    ESP_LOGI(TAG, "[APP] Startup..");
    ESP_LOGI(TAG, "[APP] Free memory: %" PRIu32 " bytes", esp_get_free_heap_size());
    ESP_LOGI(TAG, "[APP] IDF version: %s", esp_get_idf_version());

    // Initialize the GPIO event queue
    gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));

    if (gpio_evt_queue == NULL) {
        ESP_LOGE(TAG, "Error creating the queue");
        return;
    }

    // Initialize LED and button drivers
    led_driver_init();
    create_led_task();
    button_driver_init();

    ESP_LOGI(TAG, "LED and button drivers initialized");

    //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_LOGI(TAG, "ESP_WIFI_MODE_STA");

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    wifi_init_sta();

    ESP_LOGI(TAG, "WIFI INITIALIZED");

    mqtt_service_init();
    ESP_LOGI(TAG, "MQTT INITIALIZED");

    mqtt_led_bridge_init();
    ESP_LOGI(TAG, "MQTT LED BRIDGE INITIALIZED");

    ESP_LOGI(TAG, "Initialization complete");
}
