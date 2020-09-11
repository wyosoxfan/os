#pragma once
#include "stdio.c"
#include "typedefs.c"
#define VGA_MEMORY (uint_8*)0x8000

unsigned short CursorPosition;

void SetCursorPosition(uint_16 position) {
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint_8)(position & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint_8)((position >> 8) & 0xFF));

    CursorPosition = position;
}