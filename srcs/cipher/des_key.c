#include "ft_ssl.h"

static uint8_t g_cd[64] =
{
	56,	48, 40,	32,	24,	16,	8, 7,
	0, 57, 49, 41, 33, 25, 17, 15,
	9, 1, 58, 50, 42, 34, 26, 23,
	18, 10, 2, 59, 51, 43, 35, 31,
	62, 54, 46, 38, 30, 22, 14, 39,
	6, 61, 53, 45, 37, 29, 21, 47,
	13, 5, 60, 52, 44, 36, 28, 55,
	20, 12, 4, 27, 19, 11, 3, 63
};

static uint8_t g_sh[16] =
{
	1, 1, 2, 2, 2, 2, 2, 2,	1, 2, 2, 2, 2, 2, 2, 1
};

static uint64_t g_k[16];

static uint8_t	fix_high_bit(uint8_t byte)
{
	uint8_t		res;
	int			ones;

	res = byte;
	ones = (byte % 2) ? 1 : 0;
	while ((byte >>= 1))
		if (byte % 2)
			ones++;
	return ((ones % 2) ? res : _invert_bit(res, 7));
}

void			init_keys(uint64_t key)
{
	uint8_t		*key_ptr;
	int			i;

	key_ptr = (uint8_t *)&key;
	i = -1;
	while (++i < 8)
		key_ptr[i] = fix_high_bit(key_ptr[i]);
	i = -1;
	while (++i < 64)
		key = swap_bits(key, i, g_cd[i]);
	i = -1;
	g_k[0] = LROT((uint32_t)key, g_sh[0]) +
	((uint64_t)LROT((uint32_t)(key >> 32), g_sh[0]) << 32);
	while (++i < 16)
		g_k[i] = LROT((uint32_t)g_k[i - 1], g_sh[i]) +
		((uint64_t)LROT((uint32_t)(g_k[i - 1] >> 32), g_sh[i]) << 32);
	
}