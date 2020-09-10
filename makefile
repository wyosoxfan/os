clean:
	rm -f *.bin
boot.bin:  boot.asm
	nasm boot.asm -f bin -o boot.bin
install:  boot.bin
	qemu-img create -f raw hd.img 10M
	dd if=boot.bin of=hd.img conv=notrunc
	qemu-system-x86_64 -drive file=hd.img,format=raw