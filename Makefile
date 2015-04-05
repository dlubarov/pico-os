GCC = i686-elf-gcc -O0
GPP = i686-elf-g++ -O0 -c -nostdlib -nostartfiles -nodefaultlibs -fno-builtin -fno-exceptions -fno-rtti -fno-stack-protector
LD = i686-elf-ld
QEMU = @qemu-system-i386
objects = boot.o kernel.o console.o graphics.o memory.o panic.o random.o itoa.o icxxabi.o hash.o tar.o \
          suite.o testframework.o teststring.o testcircularbuffer.o testdeque.o testvector.o testhashmap.o

demo: kernel.iso
	$(QEMU) -m 128 -cdrom kernel.iso # 2> /dev/null

kernel.iso: kernel.bin initrd.bin
	rm -rf isodir
	mkdir -p isodir/boot/grub
	cp kernel.bin isodir/boot
	cp initrd.bin isodir/boot
	cp grub.cfg isodir/boot/grub
	grub-mkrescue -o kernel.iso isodir

initrd.bin:
	./generate-initrd

kernel.bin: $(objects) linker.ld
	$(LD) -T linker.ld -o kernel.bin $(objects) $(tests)

boot.o: boot.s multiboot.h
	$(GCC) -c boot.s

kernel.o: kernel.cpp tests common.h multiboot.h icxxabi.h tar.h util/hashmap.h util/pair.h util/vector.h util/deque.h
	$(GPP) kernel.cpp

itoa.o: itoa.cpp common.h
	$(GPP) itoa.cpp

console.o: console.cpp common.h
	$(GPP) console.cpp

graphics.o: graphics.cpp common.h
	$(GPP) graphics.cpp

tar.o: tar.cpp util/blob.h util/hashmap.h
	$(GPP) tar.cpp

memory.o: memory.cpp common.h
	$(GPP) memory.cpp

panic.o: panic.cpp common.h
	$(GPP) panic.cpp

random.o: random.cpp common.h
	$(GPP) random.cpp

hash.o: util/hash.cpp util/hash.h
	$(GPP) util/hash.cpp

icxxabi.o: icxxabi.cpp icxxabi.h
	$(GPP) icxxabi.cpp

suite.o: tests/testframework.h tests/suite.cpp tests/suite.h common.h
	$(GPP) tests/suite.cpp

testframework.o: tests/testframework.h tests/testframework.cpp common.h
	$(GPP) tests/testframework.cpp

teststring.o: tests/testframework.h tests/teststring.cpp util/string.h common.h
	$(GPP) tests/teststring.cpp

testcircularbuffer.o: tests/testframework.h tests/testcircularbuffer.cpp util/circularbuffer.h common.h
	$(GPP) tests/testcircularbuffer.cpp

testdeque.o: tests/testframework.h tests/testdeque.cpp util/deque.h util/circularbuffer.h common.h
	$(GPP) tests/testdeque.cpp

testvector.o: tests/testframework.h tests/testvector.cpp util/vector.h util/deque.h util/circularbuffer.h common.h
	$(GPP) tests/testvector.cpp

testhashmap.o: tests/testframework.h tests/testhashmap.cpp util/hashmap.h util/pair.h util/vector.h util/deque.h util/circularbuffer.h common.h
	$(GPP) tests/testhashmap.cpp

.PHONY: clean

clean:
	./cleanup
