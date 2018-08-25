#include "ft_ssl.h"

static void			init_word_array(uint8_t *chunk,
					uint64_t *w)
{
	int				i;
	uint64_t		s0;
	uint64_t		s1;

	ft_memmove(w, chunk, 128);
	i = 15;
	for (int k = 0; k < 16; k++)
	{
		reverse_uint64((uint8_t *)&w[k]);
	}
	while (++i < 80)
	{
		s0 = rrot64(w[i - 15], 1) ^
			rrot64(w[i - 15], 8) ^
			(w[i - 15] >> 7);
		s1 = rrot64(w[i - 2], 19) ^
			rrot64(w[i - 2], 61) ^
			(w[i - 2] >> 6);
		w[i] = w[i - 16] + s0 + w[i - 7] + s1;
	}
	for (int k = 0; k < 80; k++)
	{
		ft_printf("w[%d] = %.16llx\n", k, w[k]);
	}
}

static void		init_sha_lvars(uint64_t *lvars,
				t_container *sha)
{
	ft_memmove(lvars, sha->vars,
		sizeof(uint64_t) * SHA_VAR_TOTAL);
}

static void		change_hash_value(uint64_t *sha,
				uint64_t *lvars)
{
	int			i;

	i = -1;
	while (++i < SHA_VAR_TOTAL)
		sha[i] += lvars[i];
}

static void		compression_loop(uint64_t *lvars,
				uint64_t *w)
{
	int			i;
	uint64_t	t[6];

	i = -1;
	while (++i < 80)
	{
		t[0] = rrot64(lvars[H_FOUR], 14) ^
			rrot64(lvars[H_FOUR], 18) ^
			rrot64(lvars[H_FOUR], 41);
		t[1] = (lvars[H_FOUR] & lvars[H_FIVE]) ^
			((~lvars[H_FOUR]) & lvars[H_SIX]);
		t[2] = lvars[H_SEVEN] +
			t[0] + t[1] + g_kvars_sha512[i] + w[i];
		t[3] = rrot64(lvars[H_ZERO], 28) ^
		rrot64(lvars[H_ZERO], 34) ^ rrot64(lvars[H_ZERO], 39);
		t[4] = (lvars[H_ZERO] & lvars[H_ONE]) ^
			(lvars[H_ZERO] & lvars[H_TWO]) ^
			(lvars[H_ONE] & lvars[H_TWO]);
		t[5] = t[3] + t[4];
		lvars[H_SEVEN] = lvars[H_SIX];
		lvars[H_SIX] = lvars[H_FIVE];
		lvars[H_FIVE] = lvars[H_FOUR];
		lvars[H_FOUR] = lvars[H_THREE] + t[2];
		lvars[H_THREE] = lvars[H_TWO];
		lvars[H_TWO] = lvars[H_ONE];
		lvars[H_ONE] = lvars[H_ZERO];
		lvars[H_ZERO] = t[2] + t[5];
		ft_printf("CYCLE %d: %.16llx%.16llx%.16llx%.16llx%.16llx%.16llx%.16llx%.16llx\n",
				i + 1,
				lvars[H_ZERO], lvars[H_ONE],
				lvars[H_TWO], lvars[H_THREE],
				lvars[H_FOUR], lvars[H_FIVE],
				lvars[H_SIX], lvars[H_SEVEN]);
	}
}

void				proceed_chunk_sha512(t_container *sha,
					uint8_t *chunk)
{
	uint64_t	w[80];
	uint64_t	lvars[SHA_VAR_TOTAL];

	ft_bzero(w, 80 * sizeof(uint32_t));
	init_word_array(chunk, w);
	init_sha_lvars(lvars, sha);
	compression_loop(lvars, w);
	change_hash_value((uint64_t *)(sha->vars),
		lvars);
}