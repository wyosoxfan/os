#include "video.cpp"
#include "stdio.cpp"
#include "idt.cpp"

extern "C" void kernel_main() {
    SetCursorPosition(PositionFromCoords(0,0));
    InitializeIDT();
    return;
}