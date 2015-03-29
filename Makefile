GCC = i686-elf-gcc -O0
GPP = i686-elf-g++ -O0 -c -nostdlib -nostartfiles -nodefaultlibs -fno-builtin -fno-exceptions -fno-rtti -fno-stack-protector
LD = i686-elf-ld
QEMU = @qemu-system-i386
objects = boot.o kernel.o console.o memory.o panic.o random.o itoa.o icxxabi.o hash.o \
          suite.o testframework.o teststring.o testcircularbuffer.o testdeque.o testvector.o testhashmap.o

demo: kernel.bin
	$(QEMU) -m 512 -kernel kernel.bin # 2> /dev/null

kernel.bin: $(objects) linker.ld
	$(LD) -T linker.ld -o kernel.bin $(objects) $(tests)

boot.o: boot.S multiboot.h
	$(GCC) -c boot.S 

kernel.o: kernel.cpp tests common.h multiboot.h icxxabi.h util/hashmap.h util/pair.h util/vector.h util/deque.h
	$(GPP) kernel.cpp

itoa.o: itoa.cpp common.h
	$(GPP) itoa.cpp

console.o: console.cpp common.h
	$(GPP) console.cpp

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
