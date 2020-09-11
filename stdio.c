#pragma once

void outb(uint_16 port, uint_8 val) {
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

void inb(uint_16 port) {
    unsigned char returnVal;
    asm volatile ("inb %1, %0" : "=a"(returnVal) : "Nd"(port));
    return returnVal;
}