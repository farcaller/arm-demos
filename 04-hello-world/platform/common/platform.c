#include "platform.h"

void main()
{
    platform_init();
    platform_timer_init();
    setup();

    while(1) {
        loop();
    }
}
