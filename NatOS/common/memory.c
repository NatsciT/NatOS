#include "memory.h"



bool memcpy(byte* src, size_t src_size, byte* des, size_t des_size)
{
	size_t i;

	if (src_size > des_size) return false;

	for (i = 0; i < src_size; i++)
		des[i] = src[i];

	return true;
}