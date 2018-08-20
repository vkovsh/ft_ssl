#include "ft_ssl.h"

void				init_word_array(unsigned char *chunk,
					unsigned int *w)
{
	int				i;
	int				s0;
	int				s1;

	ft_memmove(w, chunk, 64);
	i = 15;
	while (++i < 64)
	{
		s0 = rrot(w[i - 15], 7) ^
			rrot(w[i - 15], 18) ^
			(w[i - 15] >> 3);
		s1 = rrot(w[i -2], 17) ^
			rrot(w[i - 2], 19) ^
			(w[i - 2] >> 10);
		w[i] = w[i - 16] + s0 + w[i - 7] + s1;
	}
}

void				init_sha_lvars(unsigned int *lvars,
					t_container *sha)
{
	int				i;

	i = -1;
	while (++i < SHA_VAR_TOTAL)
		lvars[i] = sha->vars[i];
}

void				change_hash_value(t_container *sha,
					unsigned int *lvars)
{
	int				i;

	i = -1;
	while (++i < SHA_VAR_TOTAL)
		sha->vars[i] += lvars[i];
}

void				compression_loop(unsigned int *lvars,
					unsigned int *w)
{
	int				i;
	unsigned int	t[6];

	i = -1;
	while (++i < 64)
	{
		t[0] = rrot(lvars[H_FOUR], 6) ^
		rrot(lvars[H_FOUR], 11) ^ rrot(lvars[H_FOUR], 25);
		t[1] = (lvars[H_FOUR] & lvars[H_FIVE]) ^
		((~lvars[H_FOUR]) & lvars[H_FIVE]) ^ lvars[H_SIX];
		t[2] = lvars[H_SEVEN] +
			t[0] + t[1] + k_vars_sha[i] + w[i];
		t[3] = rrot(lvars[H_ZERO], 2) ^
		rrot(lvars[H_ZERO], 13) ^ rrot(lvars[H_ZERO], 22);
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
	}
}

void				proceed_chunk_sha2(t_container *sha,
					unsigned char *chunk)
{
	unsigned int	w[64];
	unsigned int	lvars[SHA_VAR_TOTAL];

	init_word_array(chunk, w);
	init_sha_lvars(lvars, sha);
	compression_loop(lvars, w);
	change_hash_value(sha, lvars);
}