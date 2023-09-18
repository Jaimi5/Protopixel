#include "esp_log.h"
#include "led_task.h"
#include "drivers/led_driver.h"
#include "utilities/debounce.h"

static const char* TAG = "led_task";

void create_led_task(void) {
    // Create a FreeRTOS task to handle LED toggle
    xTaskCreate(led_task, "led_task", 2048, NULL, 10, NULL);
}

void led_task(void* params) {
    ESP_LOGI(TAG, "Starting the LED task");

    uint32_t gpio_num;

    while (true) {
        if (xQueueReceive(gpio_evt_queue, &gpio_num, portMAX_DELAY)) {

            // Check for debounce
            if (!check_debounce()) {
                ESP_LOGI(TAG, "GPIO %lu was pressed, but debounce prevented it", gpio_num);
                continue;
            }

            ESP_LOGI(TAG, "GPIO %lu was pressed.", gpio_num);
            change_led_state();
            blink_led();
        }
    }
}