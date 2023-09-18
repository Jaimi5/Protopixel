#include <stdio.h>
#include "esp_log.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_timer.h"

static const char* TAG = "LED_BLINK";

#define LED_PIN GPIO_NUM_8
#define BUTTON_PIN GPIO_NUM_27

static uint8_t s_led_state = 1;
static QueueHandle_t gpio_evt_queue = NULL;

#define DEBOUNCE_TIME 200000 // 200ms
static uint64_t last_interrupt_time = 0;

static void IRAM_ATTR gpio_interrupt_handler(void* args) {
    // Cast the event type to the correct type
    uint32_t gpio_num = (uint32_t) args;

    // Send the event type and data to the interrupt handler task
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
}

static void blink_led(void) {
    // Set the GPIO level according to the state (LOW or HIGH)
    ESP_ERROR_CHECK(gpio_set_level(LED_PIN, s_led_state));

    ESP_LOGI(TAG, "LED state is %s", s_led_state ? "ON" : "OFF");
}

static void toggle_led_state(void) {
    // Toggle the LED state
    s_led_state = !s_led_state;
}

static bool check_debounce(void) {
    int64_t interrupt_time = esp_timer_get_time();
    if (interrupt_time - last_interrupt_time < DEBOUNCE_TIME)
        return false;

    last_interrupt_time = interrupt_time;
    return true;
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

            ESP_LOGI(TAG, "GPIO %lu was pressed. Led is %s", gpio_num, gpio_get_level(LED_PIN) == true ? "ON" : "OFF");
            toggle_led_state();
            blink_led();
        }
    }
}

static void configure_button_interrupt(void) {
    // Create a FreeRTOS queue to handle GPIO events
    gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));

    // Create a FreeRTOS task to handle LED toggle
    xTaskCreate(led_task, "led_task", 2048, NULL, 10, NULL);

    // Install the ISR handler for the button GPIO pin
    ESP_ERROR_CHECK(gpio_install_isr_service(0));

    // Add the handler for the specific GPIO pin
    ESP_ERROR_CHECK(gpio_isr_handler_add(BUTTON_PIN, gpio_interrupt_handler, (void*) BUTTON_PIN));
}

static void configure_button(void) {
    ESP_LOGI(TAG, "Configuring the button");

    // Reset button GPIO as input, enable pull down
    ESP_ERROR_CHECK(gpio_reset_pin(BUTTON_PIN));
    ESP_ERROR_CHECK(gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT));
    ESP_ERROR_CHECK(gpio_pulldown_en(BUTTON_PIN));
    ESP_ERROR_CHECK(gpio_pullup_dis(BUTTON_PIN));
    ESP_ERROR_CHECK(gpio_set_intr_type(BUTTON_PIN, GPIO_INTR_POSEDGE));
}

static void configure_led(void) {
    ESP_LOGI(TAG, "Configuring the LED");

    // Reset the LED GPIO
    ESP_ERROR_CHECK(gpio_reset_pin(LED_PIN));
    ESP_ERROR_CHECK(gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT));

    // Initial state is on
    blink_led();
}

void app_main(void) {
    configure_led();
    configure_button();
    configure_button_interrupt();

    ESP_LOGI(TAG, "Starting the LED blink example");
}
