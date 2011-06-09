#pragma once

#define STOP_ON_FAILURE 1

void test_category(const char *cat);

void assert(bool c, const char *message);
void assert(bool c);

void assert_false(bool c, const char *message);
void assert_false(bool c);
