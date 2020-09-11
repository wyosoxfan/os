jmp EnterProtectedMode

%include "gdt.asm"

EnterProtectedMode:
  cli 
  call EnableA20
  lgdt [gdt_descriptor]
  mov eax, cr0
  or eax, 1
  mov cr0, eax
  jmp codeseg:StartProtectedMode

EnableA20:
  in al, 0x92
  or al, 2
  out 0x92, al
  ret

[bits 32]
%include "cpu.asm"
%include "memory.asm"

StartProtectedMode:
  mov ax, dataseg
  mov ds, ax
  mov ss, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  call DetectCPUID
  call DetectLongMode
  call SetupIdentityPaging
  call EditGDT
  jmp codeseg:Start64BitMode

[bits 64]
[extern kernel_main]
Start64BitMode:
  mov edi, 0xb8000
  mov rax, 0x1f201f201f201f20
  mov ecx, 500
  rep stosq
  call kernel_main
  jmp $