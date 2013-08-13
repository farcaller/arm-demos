#ifndef PLATFORM_H
#define PLATFORM_H

void platform_setup_led();
void platform_toggle_led(int on);
void platform_clkout(int clock);

void setup();
void loop();

#endif
