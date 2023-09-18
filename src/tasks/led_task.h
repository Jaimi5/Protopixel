#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

extern QueueHandle_t gpio_evt_queue;

void create_led_task(void);
void led_task(void* params);