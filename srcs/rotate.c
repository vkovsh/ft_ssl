#include "ft_ssl.h"

unsigned int		lrot(unsigned int x, int c)
{
    return ((x << c) | (x >> (32 - c)));
}

unsigned int		rrot(unsigned int x, int c)
{
	return ((x >> c) | (x << (32 - c)));
}