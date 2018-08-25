#include "ft_ssl.h"

uint32_t		lrot(uint32_t x, int c)
{
    return ((x << c) | (x >> (32 - c)));
}

uint32_t		rrot(uint32_t x, int c)
{
	return ((x >> c) | (x << (32 - c)));
}

uint64_t		lrot64(uint64_t x, int c)
{
    return ((x << c) | (x >> (64 - c)));
}

uint64_t		rrot64(uint64_t x, int c)
{
	return ((x >> c) | (x << (64 - c)));
}