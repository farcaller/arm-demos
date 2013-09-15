#include <stdint.h>

extern uint32_t _etext;
extern uint32_t _data;
extern uint32_t _edata;
extern uint32_t _bss;
extern uint32_t _ebss;

void platform_init_data()
{
    // anything executed earlier should better not depend on global vars.

    uint32_t len = (void *)_edata - (void *)_data;
    uint32_t *src = &_etext;
    uint32_t *dst = &_data;
    for(uint32_t i = 0; i < len; ++i) {
        *dst++ = *src++;
    }

    len = (void *)_ebss - (void *)_bss;
    *dst = &_bss;
    for(uint32_t i = 0; i < len; ++i) {
        *dst++ = 0;
    }
}
