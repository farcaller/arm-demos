#include "platform.h"

void main()
{
    platform_init();
    setup();

    while(1) {
        loop();
    }
}
