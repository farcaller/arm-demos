#include "LPC11xx.h"

void platform_systick_wait()
{
    volatile int i;
    i = SysTick->CTRL;
    while((i & 0x00010000) == 0) {
       i = SysTick->CTRL;
    }
}

void platform_systick_wait_loop()
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

void platform_systick_setup()
{
    SysTick->CTRL = 0x04;
    SysTick->LOAD = 12000000;
    SysTick->VAL = 0;
    SysTick->CTRL = 0x05;
}
