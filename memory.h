#pragma once

#include "common.h"

void *raw_malloc(size_t len);
void raw_free(void *start, size_t len);
