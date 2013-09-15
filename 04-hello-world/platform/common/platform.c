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
    uint32_t *mem_addr = &_data;
    uint32_t *end_addr = &_edata;
    uint32_t len = (uint8_t *)end_addr - (uint8_t *)mem_addr;

    for (uint32_t i = 0; i < len; i += sizeof(load_addr)) {
        *mem_addr++ = *load_addr++;
    }

    mem_addr = &_bss;
    end_addr = &_ebss;
    len = (uint8_t *)end_addr - (uint8_t *)mem_addr;

    for (uint32_t i = 0; i < len; i += sizeof(load_addr)) {
        *mem_addr++ = 0;
    }
}
