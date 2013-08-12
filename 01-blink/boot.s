.cpu cortex-m0      /* ограничиваем ассемблер списком существующих инструкций */
.thumb

.word   _stack_base /* начало стека в самом конце памяти, стек растет вниз */
.word   main        /* Reset: с прерывания сразу прыгаем в код на С */
.word   hang        /* NMI и все остальные прерывания нас не сильно волнуют */
.word   hang        /* HardFault */
.word   hang        /* MemManage */
.word   hang        /* BusFault */
.word   hang        /* UsageFault */
.word   _boot_checksum /* Подпись загрузчика */
.word   hang        /* RESERVED */
.word   hang        /* RESERVED*/
.word   hang        /* RESERVED */
.word   hang        /* SVCall */
.word   hang        /* Debug Monitor */
.word   hang        /* RESERVED */
.word   hang        /* PendSV */
.word   hang        /* SysTick */
.word   hang        /* Внешнее прерывание 0 */
                    /* ... */

/* дальше идут остальные 32 прерывания у LPC1114 и 35 у LPC1768, но
   их нет смысла описывать, потому как мы их все равно не используем */

.thumb_func
hang:   b .         /* функция заглушка для прерываний: вечный цикл */

.global hang
