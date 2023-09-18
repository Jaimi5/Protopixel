#include "esp_log.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char* TAG = "LED_BLINK";

#define LED_PIN GPIO_NUM_8

static uint8_t s_led_state = 0;

static void configure_led(void) {
    ESP_LOGI(TAG, "Example configured to blink LED!");

    gpio_reset_pin(LED_PIN);

    // Set the GPIO as a push/pull output
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
}

static void blink_led(void) {
    // Set the GPIO level according to the state (LOW or HIGH)
    gpio_set_level(LED_PIN, s_led_state);
}

void app_main(void) {
    // Configure the peripheral according to the LED type
    configure_led();

    while (1) {
        ESP_LOGI(TAG, "Turning the LED %s!", s_led_state == true ? "ON" : "OFF");

        blink_led();
        /* Toggle the LED state */
        s_led_state = !s_led_state;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}