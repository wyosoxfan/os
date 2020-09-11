clean:
	rm -f *.bin
boot.bin:  boot.asm
	nasm boot.asm -f bin -o boot.bin
kernel.bin:  kernel.asm
	nasm kernel.asm -f bin -o kernel.bin
os.bin:  boot.bin kernel.bin
	cat boot.bin kernel.bin > os.bin
install:  os.bin
	qemu-img create -f raw hd.img 10M
	dd if=os.bin of=hd.img conv=notrunc
	qemu-system-x86_64 -drive file=hd.img,format=raw