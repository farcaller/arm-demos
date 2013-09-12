#include "LPC17xx.h"

#define LED_PIN       (1<<18)
#define LED_PIN_IN_B2 (1<<2)

void platform_led_setup()
{
    LPC_GPIO1->FIODIR |= LED_PIN;
}

void platform_led_toggle(int on)
{
    LPC_GPIO1->FIOMASK2 |= ~LED_PIN_IN_B2;
    if (on) {
        LPC_GPIO1->FIOSET2 = LED_PIN_IN_B2;
    } else {
        LPC_GPIO1->FIOCLR2 = LED_PIN_IN_B2;
    }
}
