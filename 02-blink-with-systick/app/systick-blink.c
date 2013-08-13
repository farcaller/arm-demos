#include "platform.h"

void setup()
{
    platform_led_setup();
    platform_systick_setup();
}

void loop()
{
    platform_led_toggle(1);
    platform_systick_wait();
    platform_led_toggle(0);
    platform_systick_wait();
}
