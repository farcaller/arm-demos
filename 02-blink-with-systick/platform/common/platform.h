#ifndef PLATFORM_H
#define PLATFORM_H

void platform_init();

void platform_led_setup();
void platform_led_toggle(int on);

void platform_clkout(int clock);

void setup();
void loop();

#endif
