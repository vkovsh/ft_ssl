#include "ft_ssl.h"

static uint8_t g_s0[28] =
{
	57, 49, 41, 33, 25, 17, 9,
	1, 58, 50, 42, 34, 26, 18,
	10, 2, 59, 51, 43, 35, 27,
	19, 11, 3, 60, 52, 44, 36
};

static uint8_t g_d0[28] =
{
	63, 55, 47, 39, 31, 23, 15,
	7, 62, 54, 46, 38, 30, 2,
	14, 6, 61, 53, 45, 37, 29,
	21, 13, 5, 28, 20, 12, 4
};

static uint64_t g_k[16] = {0};

//1 2 4 8 16 32 64 128
void		init_keys(uint64_t init_key)
{
	uint8_t	*init_key_ptr;
	int		i;

	init_key_ptr = (uint8_t *)&init_key;
	i = -1;
	while (++i < 8)
	{

	}
}