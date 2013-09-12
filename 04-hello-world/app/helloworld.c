#include "platform.h"

void setup()
{
    platform_led_setup();
    //platform_uart_setup(9600);
}

void loop()
{
    platform_led_toggle(1);
    platform_delay(500);
    platform_led_toggle(0);
    platform_delay(1000);

    //platform_delay(1000);
    //platform_uart_writef("hello world\n");
}
