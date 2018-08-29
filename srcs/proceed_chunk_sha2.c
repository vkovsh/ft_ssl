/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proceed_chunk_sha2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 13:45:32 by vkovsh            #+#    #+#             */
/*   Updated: 2018/08/29 13:45:35 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void			init_word_array(uint8_t *chunk,
					uint32_t *w)
{
	int				i;
	int				s0;
	int				s1;

	ft_memmove(w, chunk, 64);
	i = 15;
	for (int k = 0; k < 16; k++)
		reverse((uint8_t *)&w[k], sizeof(uint32_t));
	while (++i < 64)
	{
		s0 = RROT(w[i - 15], 7, 32) ^
			RROT(w[i - 15], 18, 32) ^
			(w[i - 15] >> 3);
		s1 = RROT(w[i - 2], 17, 32) ^
			RROT(w[i - 2], 19, 32) ^
			(w[i - 2] >> 10);
		w[i] = w[i - 16] + s0 + w[i - 7] + s1;
	}
}

static void		init_sha_lvars(uint32_t *lvars,
					t_container *sha)
{
	ft_memmove(lvars, sha->vars,
		sizeof(uint32_t) * SHA_VAR_TOTAL);
}

static void		change_hash_value(uint32_t *sha,
					uint32_t *lvars)
{
	int				i;

	i = -1;
	while (++i < SHA_VAR_TOTAL)
		sha[i] += lvars[i];
}

static void		compression_loop(uint32_t *lvars,
					uint32_t *w)
{
	int			i;
	uint32_t	t[6];

	i = -1;
	while (++i < 64)
	{
		t[0] = RROT(lvars[H_FOUR], 6, 32) ^
			RROT(lvars[H_FOUR], 11, 32) ^
			RROT(lvars[H_FOUR], 25, 32);
		t[1] = (lvars[H_FOUR] & lvars[H_FIVE]) ^
			((~lvars[H_FOUR]) & lvars[H_SIX]);
		t[2] = lvars[H_SEVEN] +
			t[0] + t[1] + g_kvars_sha[i] + w[i];
		t[3] = RROT(lvars[H_ZERO], 2, 32) ^
		RROT(lvars[H_ZERO], 13, 32) ^ RROT(lvars[H_ZERO], 22, 32);
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
					uint8_t *chunk)
{
	uint32_t	w[64];
	uint32_t	lvars[SHA_VAR_TOTAL];

	ft_bzero(w, 64 * sizeof(uint32_t));
	init_word_array(chunk, w);
	init_sha_lvars(lvars, sha);
	compression_loop(lvars, w);
	change_hash_value((uint32_t *)(sha->vars),
		lvars);
}
