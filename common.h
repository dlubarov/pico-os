#pragma once

typedef signed char int8;
typedef signed short int16;
typedef signed int int32;
typedef signed long long int64;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;
typedef uint32 size_t;

void *raw_malloc(size_t len);
void raw_free(void *start, size_t len);

void kmemcpy(void *dst, const void *src, size_t len);
void kmemset(void *mem, int value, size_t num);

uint32 randu32();
uint32 randu32_limit(uint32 upper);
uint32 randu32_range(uint32 lower, uint32 upper);

void cls();
void kputchar(int c);
void kprintf(const char *format, ...);

void panic(const char *message);
void hang();

void itoa(char *buf, int base, int d);
