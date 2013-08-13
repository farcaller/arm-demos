#include "LPC11xx.h"

void platform_clkout(int clock)
{
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);

    LPC_IOCON->PIO0_1 &= ~0x3F; // Select clkout function for P0.1
    LPC_IOCON->PIO0_1 |= 0x01;

    LPC_SYSCON->CLKOUTCLKSEL = 0x00; // IRC: 0x00 System osci: 0x01 WTD: 0x02 Main clk: 0x03

    LPC_SYSCON->CLKOUTUEN = 0x01; // Update clock
    LPC_SYSCON->CLKOUTUEN = 0x00; // Toggle update register once
    LPC_SYSCON->CLKOUTUEN = 0x01;

    while ( !(LPC_SYSCON->CLKOUTUEN & 0x01) ); // Wait until updated

    LPC_SYSCON->CLKOUTDIV = 1; // Divided by 1
}
