#include "LPC17xx.h"

#define LED_PIN       (1<<18)
#define LED_PIN_IN_B2 (1<<2)

#define GPIO_DIR_REG  0x2009C020  /* FIO1DIR задает направление для блока GPIO 1 */
#define GPIO_REG_VAL  0x2009C034  /* FIO1PIN задает значение для блока GPIO 1 */
#define GPIO_PIN_NO   (1<<18)     /* 18-й бит отвечает за 18-й пин */


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
