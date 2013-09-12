extern void main();
extern void (* const isr_vector_table[])(void);
extern void _stack_base();
extern void _boot_checksum();

__attribute__ ((weak)) void isr_nmi();
__attribute__ ((weak)) void isr_hardfault();
__attribute__ ((weak)) void isr_svcall();
__attribute__ ((weak)) void isr_pendsv();
__attribute__ ((weak)) void isr_systick();

__attribute__ ((section(".isr_vector")))
void (* const isr_vector_table[])(void) = {
    &_stack_base,
    main,             // Reset
    isr_nmi,          // NMI
    isr_hardfault,    // Hard Fault
    0,                // CM3 Memory Management Fault
    0,                // CM3 Bus Fault
    0,                // CM3 Usage Fault
    &_boot_checksum,  // NXP Checksum code
    0,                // Reserved
    0,                // Reserved
    0,                // Reserved
    isr_svcall,       // SVCall
    0,                // Reserved for debug
    0,                // Reserved
    isr_pendsv,       // PendSV
    isr_systick,      // SysTick
};

// Default handlers -- enter infinite loop
void isr_nmi(void)
{
    while(1)
        ;
}

void isr_hardfault(void)
{
    while(1)
        ;
}

void isr_svcall(void)
{
    while(1)
        ;
}

void isr_pendsv(void)
{
    while(1)
        ;
}

void isr_systick(void)
{
    while(1)
        ;
}
