#include "LPC17xx.h"
#include "platform.h"

extern uint32_t platform_clock;

// This function is bound to use UART1 only, as it's powered on boot, so we
// have less issues with it.
void platform_uart_setup(uint32_t baud_rate)
{
    // Make sure UART IRQ is disabled
    NVIC_DisableIRQ(UART1_IRQn);

    // Setup pin 0.15 (P13) as TXD
    LPC_PINCON->PINSEL0 &= ~0xc0000000;
    LPC_PINCON->PINSEL0 |=  0x40000000;

    // Setup pin 0.16 (P14) as RXD
    LPC_PINCON->PINSEL1 &= ~0x00000003;
    LPC_PINCON->PINSEL1 |=  0x00000001;

    // Figure out the divisor for UART1, it will be platform_clock/4 on boot
    // though.
    // TODO(farcaller): it seems that 4MHz with 4x divisor is too slow
    uint_fast8_t pclkdiv = (LPC_SC->PCLKSEL0 >> 8) & 0x03;
    uint32_t pclk;
    switch (pclkdiv) {
        case 0x00:
        default:
            pclk = platform_clock/4;
            break;
        case 0x01:
            pclk = platform_clock;
            break;
        case 0x02:
            pclk = platform_clock/2;
            break;
        case 0x03:
            pclk = platform_clock/8;
            break;
    }

    // Setup format: 8N1, enable access to divisor latches
    LPC_UART1->LCR = 0x83;

    // Setup baud rate
    uint32_t Fdiv = (pclk / 16) / baud_rate;


    LPC_UART1->DLM = Fdiv / 256;
    LPC_UART1->DLL = Fdiv % 256;

    // Disable access to divisor latches
    LPC_UART1->LCR = 0x03;

    // Enable and reset FIFOs
    LPC_UART1->FCR = 0x07;

    // Read to reset LSR
    volatile uint32_t unused = LPC_UART1->LSR;

    // Make sure there's no data
    while(( LPC_UART1->LSR & (0x20|0x40)) != (0x20|0x40) )
        ;
    while( LPC_UART1->LSR & 0x01 ) {
        unused = LPC_UART1->RBR;
    }

    // Enable UART IRQ
    // NVIC_EnableIRQ(UART1_IRQn);

    // Enable UART IRQs on received data
    // LPC_UART1->IER = 0b101;
}

void platform_uart_putc(const char c)
{
    while( !(LPC_UART1->LSR & 0x20) )
        ;
    LPC_UART1->THR = c;
}
