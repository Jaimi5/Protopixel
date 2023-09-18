#pragma once

#include "driver/gpio.h"

void led_driver_init(void);
void blink_led(void);
void change_led_state(void);