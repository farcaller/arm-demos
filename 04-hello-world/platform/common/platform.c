#include "platform.h"

extern uint32_t _data_load;
extern uint32_t _data;
extern uint32_t _edata;
extern uint32_t _bss;
extern uint32_t _ebss;

void main()
{
    platform_init();
    platform_init_data();
    platform_init_post();

    platform_timer_init();

    setup();

    while(1) {
        loop();
    }
}

void platform_init_data()
{
    uint32_t *load_addr = &_data_load;

    for (uint32_t *mem_addr = &_data; mem_addr < &_edata; ) {
        *mem_addr++ = *load_addr++;
    }

    for (uint32_t *mem_addr = &_bss; mem_addr < &_ebss; ) {
        *mem_addr++ = 0;
    }
}
