#include "debounce.h"
#include "esp_timer.h"
#include "config.h"

static int64_t last_interrupt_time = 0;

uint8_t check_debounce(void) {
    int64_t interrupt_time = esp_timer_get_time();
    if (interrupt_time - last_interrupt_time < DEBOUNCE_TIME)
        return false;

    last_interrupt_time = interrupt_time;
    return true;
}
