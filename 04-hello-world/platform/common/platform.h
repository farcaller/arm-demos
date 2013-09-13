#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdint.h>

void platform_init();
void platform_timer_init();

void platform_led_setup();
void platform_led_toggle(int on);

void platform_clkout(int clock);

void platform_delay(uint_fast32_t msec);

void platfrom_uart_setup(uint_fast32_t baud);
int platform_uart_printf(const char *format, ...);

void setup();
void loop();

#endif
