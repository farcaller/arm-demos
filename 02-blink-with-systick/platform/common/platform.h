#ifndef PLATFORM_H
#define PLATFORM_H

void platform_init();

void platform_led_setup();
void platform_led_toggle(int on);

void platform_systick_setup();
void platform_systick_wait_loop();
void platform_systick_wait();

void platform_clkout(int clock);

void setup();
void loop();

#endif
