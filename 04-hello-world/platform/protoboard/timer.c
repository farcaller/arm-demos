#include "LPC11xx.h"
#include <stdint.h>

extern uint32_t platform_clock;
static volatile uint32_t systick_10ms_ticks = 0;

void platform_delay(uint32_t msec)
{
    uint32_t tenms = msec / 10;
    uint32_t dest_time = systick_10ms_ticks + tenms;
    while(systick_10ms_ticks < dest_time) {
        __WFI();
    }
}

void platform_timer_init()
{
    systick_10ms_ticks = 0; // BSS is not zeroed out [yet]
    SysTick->CTRL = 0b110;
    SysTick->LOAD = platform_clock / 100; // 10ms
    SysTick->VAL = 0;
    SysTick->CTRL = 0b111;
}

// override isr_systick from isr.c
void isr_systick(void)
{
    ++systick_10ms_ticks;
}
