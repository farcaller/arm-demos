#include "LPC11xx.h"
#include "platform.h"

int platform_clock;
int __section_table_start, __data_section_table, __data_section_table_end,
    __bss_section_table, __bss_section_table_end,
    __section_table_end, _data, _edata, _bss, _ebss;

#define PRINT_ADDR(a) platform_uart_printf("  " #a " = 0x%08x\n", &a)

const char const *habr = "habr";

void setup()
{
    platform_led_setup();
    platform_uart_setup(9600);

    platform_delay(1000);

    platform_uart_printf("Hello %s! this is LPC1114 running at %dMHz\n", habr, platform_clock / 1000000);
    platform_uart_printf("Some layout info:\n");

    PRINT_ADDR(__section_table_start);
    PRINT_ADDR(__data_section_table);
    PRINT_ADDR(__data_section_table_end);
    PRINT_ADDR(__bss_section_table);
    PRINT_ADDR(__bss_section_table_end);
    PRINT_ADDR(__section_table_end);

    PRINT_ADDR(_data);
    PRINT_ADDR(_edata);
    PRINT_ADDR(_bss);
    PRINT_ADDR(_ebss);
}

void loop()
{
    __WFI();
}

