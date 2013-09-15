#include "platform.h"

extern uint32_t _data;
extern uint32_t _edata;
extern uint32_t _bss;
extern uint32_t _ebss;

#define PRINT_ADDR(a) platform_uart_printf("  " #a " = 0x%08x\n", &a)

const char * const habr = "habr";

int static_int = 0xab;
int this_one_is_zero;

void setup()
{
    platform_led_setup();
    platform_uart_setup(9600);

    platform_delay(1000);

    platform_led_toggle(1);

    platform_uart_printf("Hello %s! this is LPC1114 running at %dMHz\n", habr, platform_clock / 1000000);
    platform_uart_printf("Some layout info:\n");

    PRINT_ADDR(_data);
    PRINT_ADDR(_edata);
    PRINT_ADDR(_bss);
    PRINT_ADDR(_ebss);

    platform_uart_printf("Here's an int from .data:\n"
                         "  &static_int == 0x%08x\n"
                         "   static_int == 0x%08x\n",
                         &static_int, static_int);

    platform_uart_printf("Here's one from .bss:\n"
                         "  &this_one_is_zero == 0x%08x\n"
                         "   this_one_is_zero == 0x%08x\n",
                         &this_one_is_zero, this_one_is_zero);
}

void loop()
{
    __asm__ volatile ("wfi");
}

