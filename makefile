clean:
	rm -f *.bin
	rm -f *.tmp
	rm -f *.o
boot.bin:  boot.asm
	nasm boot.asm -f bin -o boot.bin
kernela.o:  kernel.asm
	nasm kernel.asm -f elf64 -o kernela.o
kernelc.o:  kernel.c
	~/opt/cross/bin/x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "kernel.c" -o "kernelc.o"
kernel.bin:  kernela.o kernelc.o
	~/opt/cross/bin/x86_64-elf-ld -T "linker.ld"
os.bin:  boot.bin kernel.bin
	cat boot.bin kernel.bin > os.bin
install:  os.bin
	qemu-img create -f raw hd.img 10M
	dd if=os.bin of=hd.img conv=notrunc
	qemu-system-x86_64 -drive file=hd.img,format=raw