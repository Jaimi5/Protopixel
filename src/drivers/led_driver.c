#include "led_driver.h"
#include "esp_log.h"
#include "config.h"

static const char* TAG = "LED_DRIVER";

static uint8_t s_led_state = false;

void led_driver_init(void) {
    ESP_LOGI(TAG, "Configuring the LED");

    // Reset the LED GPIO
    ESP_ERROR_CHECK(gpio_reset_pin(LED_PIN));
    ESP_ERROR_CHECK(gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT));

    // Initial state is on
    blink_led();
}

void blink_led(void) {
    ESP_ERROR_CHECK(gpio_set_level(LED_PIN, s_led_state));
    ESP_LOGI(TAG, "LED state is %s", s_led_state ? "ON" : "OFF");
}

void change_led_state(void) {
    s_led_state = !s_led_state;
    blink_led();
}

void set_led_state(uint8_t state) {
    s_led_state = state;
    blink_led();
}

uint8_t get_led_state(void) {
    return s_led_state;
}