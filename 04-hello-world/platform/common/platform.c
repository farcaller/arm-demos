#include "platform.h"

void main()
{
    platform_init();
    platform_init_data();
    platform_timer_init();
    setup();

    while(1) {
        loop();
    }
}
