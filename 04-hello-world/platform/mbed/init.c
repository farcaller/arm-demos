#include "LPC17xx.h"

#define CLOCK_MODE_IRC           0 // 4MHz
#define CLOCK_MODE_IRC_WITH_PLL  1 // 100 MHz
#define CLOCK_MODE_MAIN          2 // 12 MHz with external 12MHz crystal
#define CLOCK_MODE_MAIN_WITH_PLL 3 // 100 MHz with external 12MHz crystal

#define CLOCK_MODE CLOCK_MODE_IRC_WITH_PLL

uint32_t platform_clock;

void platform_init()
{
    // set up main oscillator if required
#if CLOCK_MODE == CLOCK_MODE_MAIN || CLOCK_MODE == CLOCK_MODE_MAIN_WITH_PLL
    // enable main oscillator, range: 1-20 MHz
    LPC_SC->SCS = 0x20;

    // wait for it to become ready
    while (!(LPC_SC->SCS & (1<<6)))
        ;

    // switch system clock to main oscillator
    LPC_SC->CLKSRCSEL = 0b01;
#endif

// set up PLL if it's used
#if CLOCK_MODE == CLOCK_MODE_IRC_WITH_PLL || CLOCK_MODE == CLOCK_MODE_MAIN_WITH_PLL
    // if we go for clock > 80 MHz, we need to set up flash access time
    LPC_SC->FLASHCFG = (LPC_SC->FLASHCFG & 0xFFF) | 0x4000; // 4 cpu clocks

    // set up PLL dividers
    // input  clock must be in range of 32 kHZ  to 50 MHz
    // output clock must be in range of 275 MHz to 550 MHz
#if CLOCK_MODE == CLOCK_MODE_IRC_WITH_PLL
    LPC_SC->PLL0CFG = ((1-1)<<16)|((50-1)<<0); // M = 50, N = 1
                                               // PLLclk = (4 MHz * M * 2) / N
                                               //        = 400 MHz
#else
    LPC_SC->PLL0CFG = ((3-1)<<16)|((50-1)<<0); // M = 50, N = 3
                                               // PLLclk = (12 MHz * M * 2) / N
                                               //        = 400 MHz
#endif

    // write changes
    LPC_SC->PLL0FEED = 0xAA;
    LPC_SC->PLL0FEED = 0x55;

    // enable PLL, this does NOT switch Cclk to PLL
    // otherwise you'll fuck it up with 400 MHz output
    LPC_SC->PLL0CON  = 0b01;

    // write changes
    LPC_SC->PLL0FEED = 0xAA;
    LPC_SC->PLL0FEED = 0x55;

    // wait until PLL is enabled
    while (!(LPC_SC->PLL0STAT & (1<<24)))
        ;

    // divide PLLclk by 4 to get Cclk (100 MHz)
    LPC_SC->CCLKCFG = 3;

    // wait until PLL is locked
    while (!(LPC_SC->PLL0STAT & (1<<26)))
        ;

    // connect PLL (this switches Cclk to be driven by PLL output
    // instead of bypassing it)
    LPC_SC->PLL0CON = 0b11;

    // write changes
    LPC_SC->PLL0FEED = 0xAA;
    LPC_SC->PLL0FEED = 0x55;

    // wait until PLL is connected
    while (!(LPC_SC->PLL0STAT & (1<<25)))
        ;
#endif
}

void platform_init_post()
{
#if CLOCK_MODE == CLOCK_MODE_IRC
    platform_clock = 4000000;
#elif CLOCK_MODE == CLOCK_MODE_IRC_WITH_PLL
    platform_clock = 100000000;
#elif CLOCK_MODE == CLOCK_MODE_MAIN
    platform_clock = 12000000;
#elif CLOCK_MODE == CLOCK_MODE_MAIN_WITH_PLL
    platform_clock = 100000000;
#else
    #error unknown clock mode, cannot set platform_clock
#endif
}
