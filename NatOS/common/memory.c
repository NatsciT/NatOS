#include "memory.h"



void memcpy(void* src, void* des, size_t count)
{
	size_t i;

	for (i = 0; i < count; i++) ((byte*)des)[i] = ((byte*)src)[i];
}

void memset(void* target, byte val, size_t count)
{
	size_t i;

	for (i = 0; i < count; i++) ((byte*)target)[i] = val;
}