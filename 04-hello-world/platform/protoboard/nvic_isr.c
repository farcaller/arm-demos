#define WEAK __attribute__ ((weak))
#define ALIAS(f) #f)))

__attribute__ ((weak)) void isr_default_handler();

void isr_pin_wakeup (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_spi_1 (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_i2c (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_timer16_0 (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_timer16_1 (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_timer_32_0 (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_timer_32_1 (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_spi_0 (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_uart (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_adc (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_wdt (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_bod (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_gpio_3 (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_gpio_2 (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_gpio_1 (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_gpio_0 (void) __attribute__ ((weak, alias("isr_default_handler")));

extern void (* const isr_vector_table_nvic[])(void);

__attribute__ ((section(".isr_vector_nvic")))
void (* const isr_vector_table_nvic[])(void) = {
    // s.a. lpc111x user manual, table 54 (chapter 6.4)
    // Deep-sleep wakeup
    isr_pin_wakeup,  // PIO0_0
    isr_pin_wakeup,  // PIO0_1
    isr_pin_wakeup,  // PIO0_2
    isr_pin_wakeup,  // PIO0_3
    isr_pin_wakeup,  // PIO0_4
    isr_pin_wakeup,  // PIO0_5
    isr_pin_wakeup,  // PIO0_6
    isr_pin_wakeup,  // PIO0_7
    isr_pin_wakeup,  // PIO0_8
    isr_pin_wakeup,  // PIO0_9
    isr_pin_wakeup,  // PIO0_10
    isr_pin_wakeup,  // PIO0_11
    isr_pin_wakeup,  // PIO1_0

    0,               // C_CAN is not available
    isr_spi_1,       // SPI/SSP1
    isr_i2c,         // I2C
    isr_timer16_0,   // 16-bit Timer 0
    isr_timer16_1,   // 16-bit Timer 1
    isr_timer_32_0,  // 32-bit Timer 0
    isr_timer_32_1,  // 32-bit Timer 1
    isr_spi_0,       // SPI/SSP0
    isr_uart,        // UART

    0,               // Reserved
    0,               // Reserved

    isr_adc,         // A/D Converter
    isr_wdt,         // Watchdog Timer
    isr_bod,         // Brownout Detect
    0,               // Reserved
    isr_gpio_3,      // GPIO Port 3
    isr_gpio_2,      // GPIO Port 2
    isr_gpio_1,      // GPIO Port 1
    isr_gpio_0,      // GPIO Port 0
};

void isr_default_handler(void)
{
    while(1)
        ;
}
