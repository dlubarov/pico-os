GCC = i386-elf-gcc
LD = i386-elf-ld
QEMU = qemu-system-i386

test : kernel.bin
	$(QEMU) -m 512 -kernel kernel.bin

kernel.bin : kernel.o boot.o linker.ld
	$(LD) -T linker.ld -o kernel.bin boot.o kernel.o

boot.o : boot.S multiboot.h
	$(GCC) -o boot.o -c boot.S 

kernel.o : kernel.c multiboot.h
	$(GCC) -o kernel.o -c -nostdlib -nostartfiles -nodefaultlibs kernel.c

.PHONY : clean

clean :
	rm *.o *.bin
