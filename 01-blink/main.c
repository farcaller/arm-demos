#if defined(__ARM_ARCH_6M__)

/* Cortex-M0 это ARMv6-M, код для LPC1114 */

#define GPIO_DIR_REG  0x50018000  /* GPIO1DIR  задает направление для блока GPIO 1 */
#define GPIO_REG_VAL  0x50013FFC  /* GPIO1DATA задает значение для блока GPIO 1 */
#define GPIO_PIN_NO   (1<<8)      /* 8-й бит отвечает за 8-й пин */

#else

/* Иначе просто считаем что это LPC1768 */

#define GPIO_DIR_REG  0x2009C020  /* FIO1DIR задает направление для блока GPIO 1 */
#define GPIO_REG_VAL  0x2009C034  /* FIO1PIN задает значение для блока GPIO 1 */
#define GPIO_PIN_NO   (1<<18)     /* 18-й бит отвечает за 18-й пин */

#endif

void wait()
{
  volatile int i=0xa000;
  while(i>0) {
    --i;
  }
}

void main()
{
    *((volatile unsigned int *)GPIO_DIR_REG) = GPIO_PIN_NO;

    while(1) {
        *((volatile unsigned int *)GPIO_REG_VAL) = GPIO_PIN_NO;
        wait();
        *((volatile unsigned int *)GPIO_REG_VAL) = 0;
        wait();
    }

    /* main() *никогда* не должен вернуться! */
}
