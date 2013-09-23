#define WEAK __attribute__ ((weak))
#define ALIAS(f) #f)))

void isr_default_handler();

void isr_wdt (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_timer_0 (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_timer_1 (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_timer_2 (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_timer_3 (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_uart_0 (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_uart_1 (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_uart_2 (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_uart_3 (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_pwm_1 (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_i2c_0 (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_i2c_1 (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_i2c_2 (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_spi (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_ssp_0 (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_ssp_1 (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_pll_0 (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_rtc (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_eint_0 (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_eint_1 (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_eint_2 (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_eint_3 (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_adc (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_bod (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_usb (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_can (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_dma (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_i2s (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_enet (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_rit (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_mcpwm (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_qei (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_pll_1 (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_usb_activity (void) __attribute__ ((weak, alias("isr_default_handler")));
void isr_can_activity (void) __attribute__ ((weak, alias("isr_default_handler")));

extern void (* const isr_vector_table_nvic[])(void);

__attribute__ ((section(".isr_vector_nvic")))
void (* const isr_vector_table_nvic[])(void) = {
    // s.a. lpc17xx user manual, table 50 (chapter 6.3)
    isr_wdt,
    isr_timer_0,
    isr_timer_1,
    isr_timer_2,
    isr_timer_3,
    isr_uart_0,
    isr_uart_1,
    isr_uart_2,
    isr_uart_3,
    isr_pwm_1,
    isr_i2c_0,
    isr_i2c_1,
    isr_i2c_2,
    isr_spi,
    isr_ssp_0,
    isr_ssp_1,
    isr_pll_0,
    isr_rtc,
    isr_eint_0,
    isr_eint_1,
    isr_eint_2,
    isr_eint_3,
    isr_adc,
    isr_bod,
    isr_usb,
    isr_can,
    isr_dma,
    isr_i2s,
    isr_enet,
    isr_rit,
    isr_mcpwm,
    isr_qei,
    isr_pll_1,
    isr_usb_activity,
    isr_can_activity,
};

void isr_default_handler(void)
{
    while(1)
        ;
}
