#include "LPC11xx.h"
#include "platform.h"

extern uint32_t platform_clock;

void platform_uart_setup(uint32_t baud_rate)
{
    // Make sure UART IRQ is disabled
    NVIC_DisableIRQ(UART_IRQn);

    // Enable I/O configuration block clock
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);

    // Setup pin 1_6 as RXD
    LPC_IOCON->PIO1_6 &= ~0x07;
    LPC_IOCON->PIO1_6 |= 0x01;

    // Setup pin 1_7 as TXD
    LPC_IOCON->PIO1_7 &= ~0x07;
    LPC_IOCON->PIO1_7 |= 0x01;

    // Enable & configure UART clock
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<12);
    LPC_SYSCON->UARTCLKDIV = 0x1;

    // Setup format: 8N1, enable access to divisor latches
    LPC_UART->LCR = 0x83;

    // Setup baud rate, which is based on system clock
    uint32_t Fdiv = platform_clock // take cpu clock
            / LPC_SYSCON->SYSAHBCLKDIV // divide by ABH clock
            / LPC_SYSCON->UARTCLKDIV // divide further by UART clock
            / 16 // divisor latch is 16x the desired baud rate
            / baud_rate;

    LPC_UART->DLM = Fdiv / 256;
    LPC_UART->DLL = Fdiv % 256;

    LPC_UART->FDR = 0x00 | (1 << 4) | 0;

    // Disable access to divisor latches
    LPC_UART->LCR = 0x03;

    // Enable and reset FIFOs
    LPC_UART->FCR = 0x07;

    // Read to reset LSR
    volatile uint32_t unused = LPC_UART->LSR;

    // Make sure there's no data
    while(( LPC_UART->LSR & (0x20|0x40)) != (0x20|0x40) )
        ;
    while( LPC_UART->LSR & 0x01 ) {
        unused = LPC_UART->RBR;
    }

    // Enable UART IRQ
    NVIC_EnableIRQ(UART_IRQn);

    // Enable UART IRQs on received data
    LPC_UART->IER = 0b101;
}

void platform_uart_putc(const char c)
{
    while( !(LPC_UART->LSR & 0x20) )
        ;
    LPC_UART->THR = c;
}
