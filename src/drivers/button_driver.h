#pragma once

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

extern QueueHandle_t gpio_evt_queue;

void button_driver_init();
void configure_button_interrupt();
void gpio_interrupt_handler(void* args);
