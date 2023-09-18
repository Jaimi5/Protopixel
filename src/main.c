#include "esp_log.h"
#include "drivers/button_driver.h"
#include "drivers/led_driver.h"
#include "tasks/led_task.h"

QueueHandle_t gpio_evt_queue = NULL;

static const char* TAG = "main";


void app_main(void) {
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

    ESP_LOGI(TAG, "Starting the LED blink example");
}
