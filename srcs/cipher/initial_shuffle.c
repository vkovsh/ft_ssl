#include "ft_ssl.h"

static const uint8_t g_shuffle[64] = {
58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7};

static uint64_t	swap_bits(uint64_t block,
				int a, int b)
{
	bool		is_a_set;
	bool		is_b_set;

	is_a_set = block & ((typeof(block))1 << a);
	is_b_set = block & ((typeof(block))1 << b);
	block = (is_a_set) ? SET_BIT(block, b) :
					UNSET_BIT(block, b);
	block = (is_b_set) ? SET_BIT(block, a) :
					UNSET_BIT(block, a);
	return (block);
}

uint64_t		initial_shuffle(uint64_t block)
{
	int			i;

	i = -1;
	while (++i < 64)
		block = swap_bits(block, i, g_shuffle[i]);
	return (block);
}