#pragma once
#include "stdio.cpp"
#include "typedefs.cpp"
#define VGA_MEMORY (uint_8*)0xb8000
#define VGA_WIDTH 80

#define FOREGROUND_BLACK 0x00
#define FOREGROUND_BLUE 0x01
#define FOREGROUND_GREEN 0x02
#define FOREGROUND_CYAN 0x03
#define FOREGROUND_RED 0x04
#define FOREGROUND_MAGENTA 0x05
#define FOREGROUND_BROWN 0x06
#define FOREGROUND_LIGHTGRAY 0x07
#define FOREGROUND_DARKGRAY 0x08
#define FOREGROUND_LIGHTBLUE 0x09
#define FOREGROUND_LIGHTGREEN 0x0A
#define FOREGROUND_LIGHTCYAN 0x0B
#define FOREGROUND_LIGHTRED 0x0C
#define FOREGROUND_LIGHTMAGENTA 0x0D
#define FOREGROUND_YELLOW 0x0E
#define FOREGROUND_WHITE 0x0F

#define BACKGROUND_BLACK 0x00
#define BACKGROUND_BLUE 0x10
#define BACKGROUND_GREEN 0x20
#define BACKGROUND_CYAN 0x30
#define BACKGROUND_RED 0x40
#define BACKGROUND_MAGENTA 0x50
#define BACKGROUND_BROWN 0x60
#define BACKGROUND_LIGHTGRAY 0x70
#define BACKGROUND_BLINKINGBLACK 0x80
#define BACKGROUND_BLINKINGBLUE 0x90
#define BACKGROUND_BLINKINGGREEN 0xA0
#define BACKGROUND_BLINKINGCYAN 0xB0
#define BACKGROUND_BLINKINGRED 0xC0
#define BACKGROUND_BLINKINGMAGENTA 0xD0
#define BACKGROUND_BLINKINGYELLOW 0xE0
#define BACKGROUND_BLINKINGWHITE 0xF0

uint_16 CursorPosition;

void ClearScreen(uint_64 ClearColor = BACKGROUND_BLACK | FOREGROUND_WHITE) {
  uint_64 value = 0;
  value += ClearColor << 8;
  value += ClearColor << 24;
  value += ClearColor << 40;
  value += ClearColor << 56;
  for (uint_64* i = (uint_64*)VGA_MEMORY; i < (uint_64*)VGA_MEMORY + 4000; i++) {
    *i = value;
  }
}

void SetCursorPosition(uint_16 position) {
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint_8)(position & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint_8)((position >> 8) & 0xFF));
    CursorPosition = position;
}

uint_16 PositionFromCoords(uint_8 x, uint_8 y) {
    return y * VGA_WIDTH + x;
}

void PrintChar(char chr, uint_8 color = BACKGROUND_BLACK | FOREGROUND_WHITE) {
  *(VGA_MEMORY + CursorPosition * 2) = chr;
  *(VGA_MEMORY + CursorPosition * 2 + 1) = color;
  SetCursorPosition(CursorPosition + 1);
}

void PrintString(const char* str, uint_8 color = BACKGROUND_BLACK | FOREGROUND_WHITE) {
    uint_8* charPtr = (uint_8*)str;
    uint_16 index = CursorPosition;
    while(*charPtr != 0)
    {
        switch(*charPtr) {
            case 10:
              index += VGA_WIDTH;
              break;
            case 13:
              index -= index % VGA_WIDTH;
              break;
            default:
              *(VGA_MEMORY + index * 2) = *charPtr;
              *(VGA_MEMORY + index * 2 + 1) = color;
              index++;
        }
        charPtr++;
    }
    SetCursorPosition(index);
}

char hexToStringOutput[128];
template<typename T>
const char* HexToString(T value) {
  T* valPtr = &value;
  uint_8* ptr;
  uint_8 temp;
  uint_8 size = (sizeof(T)) * 2 - 1;
  uint_8 i;
  for(i =0; i < size; i++) {
    ptr = ((uint_8*)valPtr + i);
    temp = ((*ptr & 0xF0) >> 4);
    hexToStringOutput[size - (i * 2 + 1)] = temp + (temp > 9 ? 55 : 48);
    temp = ((*ptr & 0x0F));
    hexToStringOutput[size - (i * 2 + 0)] = temp + (temp > 9 ? 55 : 48);
  }
  hexToStringOutput[size + 1] = 0;
  return hexToStringOutput;
}
