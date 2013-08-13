#include "platform.h"
#include "LPC11xx.h"

void wait()
{
    volatile int i;
    volatile int j;
    for(j=0; j<3; ++j) {
        i = SysTick->CTRL;
        while((i & 0x00010000) == 0) {
           i = SysTick->CTRL;
        }
    }
}

void setup()
{
    platform_setup_led();

    SysTick->CTRL = 0x04;
    SysTick->LOAD = 12000000;
    SysTick->CTRL = 0x05;
}

void loop()
{
    platform_toggle_led(1);
    wait();
    platform_toggle_led(0);
    wait();
}
