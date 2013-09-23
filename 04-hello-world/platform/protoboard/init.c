#include "LPC11xx.h"

#define CLOCK_MODE_IRC          0 // 12MHz
#define CLOCK_MODE_IRC_WITH_PLL 1 // 48MHz
#define CLOCK_MODE_SYS_WITH_PLL 2 // 48 MHz with external 12MHz crystal

#define CLOCK_MODE CLOCK_MODE_IRC

uint32_t platform_clock;

void platform_init()
{
// set up system oscillator and toggle PLL to point at it
#if CLOCK_MODE == CLOCK_MODE_SYS_WITH_PLL
    int i;

    // power up system oscillator
    LPC_SYSCON->PDRUNCFG &= ~(1 << 5);

    // oscillator is not bypassed, runs at 1-20MHz range
    LPC_SYSCON->SYSOSCCTRL = 0;

    // allow circutry to settle down
    for (i = 0; i < 200; ++i)
        __NOP();

    // set PLL clock source to system oscillator
    LPC_SYSCON->SYSPLLCLKSEL = 1;

    // wait for PLL clock source to be updated
    LPC_SYSCON->SYSPLLCLKUEN = 1;
    LPC_SYSCON->SYSPLLCLKUEN = 0;
    LPC_SYSCON->SYSPLLCLKUEN = 1;
    while (!(LPC_SYSCON->SYSPLLCLKUEN & 1))
        ;
#endif

// set up PLL if it's used
#if CLOCK_MODE == CLOCK_MODE_IRC_WITH_PLL || CLOCK_MODE == CLOCK_MODE_SYS_WITH_PLL
    // set up PLL dividers
    LPC_SYSCON->SYSPLLCTRL = 0x23; // M = 3, P = 12MHz
                                   // PLLout = 12MHz * (M+1) / P = 48MHz

    // power up PLL
    LPC_SYSCON->PDRUNCFG &= ~(1 << 7);

    // wait until PLL is locked
    while (!(LPC_SYSCON->SYSPLLSTAT & 1))
        ;

    // switch main clock to be driven from PLL
    LPC_SYSCON->MAINCLKSEL = 3;

    // wait for main clock source to be updated
    LPC_SYSCON->MAINCLKUEN = 1;
    LPC_SYSCON->MAINCLKUEN = 0;
    LPC_SYSCON->MAINCLKUEN = 1;
    while (!(LPC_SYSCON->MAINCLKUEN & 1))
        ;
#endif

    // PS: CLOCK_MODE_IRC is the default boot mode, do nothing
}

void platform_init_post()
{
#if CLOCK_MODE == CLOCK_MODE_IRC_WITH_PLL || CLOCK_MODE == CLOCK_MODE_SYS_WITH_PLL
    platform_clock = 48000000;
#else
    platform_clock = 12000000;
#endif
}
