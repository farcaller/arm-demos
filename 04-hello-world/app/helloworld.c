#include "platform.h"

extern uint32_t _data;
extern uint32_t _edata;
extern uint32_t _bss;
extern uint32_t _ebss;

#define PRINT_ADDR(a) platform_uart_printf("  " #a " = 0x%08x\n", &a)

const char * const habr = "habr";
#if defined(PLATFORM_PROTOBOARD)
const char * const cpuname = "LPC1114";
#elif defined(PLATFORM_MBED)
const char * const cpuname = "LPC1768";
#endif

uint8_t this_one_is_zero;
uint16_t static_int = 0xab;
uint8_t  static_int2 = 0xab;
uint32_t static_int3 = 0xab;
uint8_t  static_int4 = 0xab;


void setup()
{
	static_int2 = static_int3 + static_int4; // just keep them used

    platform_led_setup();
    platform_uart_setup(9600);

    platform_delay(1000);

    platform_uart_printf("Hello %s! this is %s running at %dMHz\n", habr, cpuname, platform_clock / 1000000);
    platform_led_toggle(1);
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

