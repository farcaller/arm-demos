#include "LPC11xx.h"
#include <stdint.h>

static volatile uint32_t systick_10ms_ticks = 0;
static volatile uint32_t systick_wrap = 0;
uint32_t systick_clock_count;
uint32_t systick_wrap_count;

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
    SysTick->CTRL = 0b110;
    SysTick->LOAD = systick_clock_count;
    SysTick->VAL = 0;
    SysTick->CTRL = 0b111;
}

// override isr_systick from isr.c
void isr_systick(void)
{
    ++systick_wrap;
    if(systick_wrap == systick_wrap_count) {
        systick_wrap = 0;
        ++systick_10ms_ticks;
    }
}
