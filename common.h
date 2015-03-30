#pragma once

#include "multiboot.h"

#define ENABLE_ASSERTIONS 1
#if ENABLE_ASSERTIONS
#define ASSERT(c, s) do {if (!(c)) panic(s);} while (0)
#else
#define ASSERT(c, s)
#endif

typedef signed char int8;
typedef signed short int16;
typedef signed int int32;
typedef signed long long int64;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;
typedef __SIZE_TYPE__ size_t;

void *raw_malloc(size_t len);
void raw_free(void *start, size_t len);
void *kmalloc(size_t len);
void kfree(void *start);

void kmemcpy(void *dst, const void *src, size_t len);
void kmemset(void *mem, int value, size_t num);
int kstrcmp(const char *s1, const char *s2);
size_t kstrlen(const char *s);

uint32 randu32();
uint32 randu32_limit(uint32 upper);
uint32 randu32_range(uint32 lower, uint32 upper);

void cls();
void newline();
void kputchar(int c);
void kputs(const char *s);
void kprintf(const char *format, ...);

void init_graphics(vbe_mode_info_t *vbe_mode_info);
void setpixel(int x, int y, uint8 r, uint8 g, uint8 b);

void panic(const char *message);
void panic1(const char *message, int a);
void panic2(const char *message, int a, int b);
void hang();

void itoa(char *buf, int base, int d);
