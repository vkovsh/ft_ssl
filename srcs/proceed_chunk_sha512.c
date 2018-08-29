/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proceed_chunk_sha512.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 13:43:28 by vkovsh            #+#    #+#             */
/*   Updated: 2018/08/29 13:43:30 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void		init_word_array(uint8_t *chunk,
				uint64_t *w)
{
	int			i;
	uint64_t	s0;
	uint64_t	s1;

	ft_memmove(w, chunk, 128);
	i = -1;
	while (++i < 16)
		reverse((uint8_t *)&w[i], sizeof(uint64_t));
	i--;
	while (++i < 80)
	{
		s0 = RROT(w[i - 15], 1, 64) ^
			RROT(w[i - 15], 8, 64) ^
			(w[i - 15] >> 7);
		s1 = RROT(w[i - 2], 19, 64) ^
			RROT(w[i - 2], 61, 64) ^
			(w[i - 2] >> 6);
		w[i] = w[i - 16] + s0 + w[i - 7] + s1;
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
		t[0] = RROT(lvars[H4], 14, 64) ^
		RROT(lvars[H4], 18, 64) ^ RROT(lvars[H4], 41, 64);
		t[1] = (lvars[H4] & lvars[H5]) ^ ((~lvars[H4]) & lvars[H6]);
		t[2] = lvars[H7] +
		t[0] + t[1] + g_kvars_sha512[i] + w[i];
		t[3] = RROT(lvars[H0], 28, 64) ^
		RROT(lvars[H0], 34, 64) ^ RROT(lvars[H0], 39, 64);
		t[4] = (lvars[H0] & lvars[H1]) ^
		(lvars[H0] & lvars[H2]) ^ (lvars[H1] & lvars[H2]);
		t[5] = t[3] + t[4];
		lvars[H7] = lvars[H6];
		lvars[H6] = lvars[H5];
		lvars[H5] = lvars[H4];
		lvars[H4] = lvars[H3] + t[2];
		lvars[H3] = lvars[H2];
		lvars[H2] = lvars[H1];
		lvars[H1] = lvars[H0];
		lvars[H0] = t[2] + t[5];
	}
}

void			proceed_chunk_sha512(t_container *sha,
				uint8_t *chunk)
{
	uint64_t	w[80];
	uint64_t	lvars[SHA_VAR_TOTAL];

	ft_bzero(w, 80 * sizeof(uint32_t));
	init_word_array(chunk, w);
	init_sha_lvars(lvars, sha);
	compression_loop(lvars, w);
	change_hash_value((uint64_t *)(sha->vars), lvars);
}
