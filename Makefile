GCC = i386-elf-gcc -O0
GPP = i386-elf-g++ -O0 -c -nostdlib -nostartfiles -nodefaultlibs -fno-builtin -fno-exceptions -fno-rtti -fno-stack-protector
LD = i386-elf-ld
QEMU = qemu-system-i386
objects = boot.o kernel.o console.o memory.o panic.o random.o itoa.o icxxabi.o

test: kernel.bin
	$(QEMU) -m 512 -kernel kernel.bin 2> /dev/null

kernel.bin: $(objects) linker.ld
	$(LD) -T linker.ld -o kernel.bin $(objects)

boot.o: boot.S multiboot.h
	$(GCC) -c boot.S 

kernel.o: kernel.cpp common.h multiboot.h icxxabi.h
	$(GPP) kernel.cpp

itoa.o: itoa.cpp
	$(GPP) itoa.cpp

console.o: console.cpp common.h
	$(GPP) console.cpp

memory.o: memory.cpp common.h
	$(GPP) memory.cpp

panic.o: panic.cpp common.h
	$(GPP) panic.cpp

random.o: random.cpp common.h
	$(GPP) random.cpp

icxxabi.o: icxxabi.h
	$(GPP) icxxabi.cpp

.PHONY: clean

clean:
	-rm -rf *.o *.bin *.gch
