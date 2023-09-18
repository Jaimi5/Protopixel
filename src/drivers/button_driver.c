#include "esp_log.h"
#include "button_driver.h"
#include "include/config.h"

static const char* TAG = "BUTTON_DRIVER";

void button_driver_init(void) {
    ESP_LOGI(TAG, "Configuring the button");

    // Reset button GPIO as input, enable pull down
    ESP_ERROR_CHECK(gpio_reset_pin(BUTTON_PIN));
    ESP_ERROR_CHECK(gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT));
    ESP_ERROR_CHECK(gpio_pulldown_en(BUTTON_PIN));
    ESP_ERROR_CHECK(gpio_pullup_dis(BUTTON_PIN));
    ESP_ERROR_CHECK(gpio_set_intr_type(BUTTON_PIN, GPIO_INTR_POSEDGE));

    // Configure the button interrupt
    configure_button_interrupt();
}

void configure_button_interrupt(void) {
    // Install the ISR handler for the button GPIO pin
    ESP_ERROR_CHECK(gpio_install_isr_service(0));

    // Add the handler for the specific GPIO pin
    ESP_ERROR_CHECK(gpio_isr_handler_add(BUTTON_PIN, gpio_interrupt_handler, (void*) BUTTON_PIN));
}

void IRAM_ATTR gpio_interrupt_handler(void* args) {
    uint32_t gpio_num = (uint32_t) args;
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
}