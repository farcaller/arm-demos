#include "LPC11xx.h"

#define LED_PIN (1<<9)

void platform_led_setup()
{
    LPC_GPIO1->DIR |= LED_PIN;
}

void platform_led_toggle(int on)
{
    LPC_GPIO1->MASKED_ACCESS[LED_PIN] = on ? LED_PIN : 0;
}
