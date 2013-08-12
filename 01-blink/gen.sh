#!/bin/bash
arm-none-eabi-as boot.s -o boot.o
arm-none-eabi-gcc -O2 -nostdlib -nostartfiles -ffreestanding -Wall -mthumb -mcpu=cortex-m0 -c main.c -o main-c0.o
arm-none-eabi-gcc -O2 -nostdlib -nostartfiles -ffreestanding -Wall -mthumb -mcpu=cortex-m3 -c main.c -o main-c3.o
arm-none-eabi-ld -o blink-c0.elf -T mem.ld boot.o main-c0.o
arm-none-eabi-ld -o blink-c3.elf -T mem.ld boot.o main-c3.o
arm-none-eabi-objdump -D blink-c0.elf > blink-c0.lst
arm-none-eabi-objdump -D blink-c3.elf > blink-c3.lst
arm-none-eabi-objcopy blink-c0.elf blink-c0.bin -O binary
arm-none-eabi-objcopy blink-c3.elf blink-c3.bin -O binary

