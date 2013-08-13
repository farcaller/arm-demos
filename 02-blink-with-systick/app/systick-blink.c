#include "platform.h"

void setup()
{
    platform_led_setup();
#if PLATFORM == MBED
    platform_systick_setup(4000000);
#elif PLATFORM == PROTOBOARD
    platform_systick_setup(12000000);
#else
    #error Unknown platform
#endif
}

void loop()
{
    platform_led_toggle(1);
    platform_systick_wait();
    platform_led_toggle(0);
    platform_systick_wait();
}
