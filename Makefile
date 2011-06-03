GCC = i386-elf-gcc -O0
GPP = $(GCC) -c -nostdlib -nostartfiles -nodefaultlibs
LD = i386-elf-ld
QEMU = qemu-system-i386
objects = boot.o kernel.o console.o memory.o panic.o random.o itoa.o

test: kernel.bin
	$(QEMU) -m 512 -kernel kernel.bin 2> /dev/null

kernel.bin: $(objects) linker.ld
	$(LD) -T linker.ld -o kernel.bin $(objects)

boot.o: boot.S multiboot.h
	$(GCC) -c boot.S 

kernel.o: kernel.c common.h multiboot.h
	$(GPP) kernel.c

itoa.o: itoa.c
	$(GPP) itoa.c

console.o: console.c common.h
	$(GPP) console.c

memory.o: memory.c common.h
	$(GPP) memory.c

panic.o: panic.c common.h
	$(GPP) panic.c

random.o: random.c common.h
	$(GPP) random.c

.PHONY: clean

clean:
	-rm -rf *.o *.bin *.gch
