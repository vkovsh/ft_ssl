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

static void		init_word_array(uint8_t *chunk,
				uint32_t *w)
{
	int			i;
	int			s0;
	int			s1;

	ft_memmove(w, chunk, 64);
	i = -1;
	while (++i < 16)
		reverse((uint8_t *)&w[i], sizeof(uint32_t));
	i--;
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
	int			i;

	i = -1;
	while (++i < SHA_VAR_TOTAL)
		sha[i] += lvars[i];
}

static void		compression_loop(uint32_t *v,
				uint32_t *w)
{
	int			i;
	uint32_t	t[6];

	i = -1;
	while (++i < 64)
	{
		t[0] = RROT(v[H4], 6, 32) ^
		RROT(v[H4], 11, 32) ^ RROT(v[H4], 25, 32);
		t[1] = (v[H4] & v[H5]) ^ ((~v[H4]) & v[H6]);
		t[2] = v[H7] + t[0] + t[1] + g_kvars_sha[i] + w[i];
		t[3] = RROT(v[H0], 2, 32) ^
		RROT(v[H0], 13, 32) ^ RROT(v[H0], 22, 32);
		t[4] = (v[H0] & v[H1]) ^
			(v[H0] & v[H2]) ^ (v[H1] & v[H2]);
		t[5] = t[3] + t[4];
		v[H7] = v[H6];
		v[H6] = v[H5];
		v[H5] = v[H4];
		v[H4] = v[H3] + t[2];
		v[H3] = v[H2];
		v[H2] = v[H1];
		v[H1] = v[H0];
		v[H0] = t[2] + t[5];
	}
}

void			proceed_chunk_sha2(t_container *sha,
				uint8_t *chunk)
{
	uint32_t	w[64];
	uint32_t	lvars[SHA_VAR_TOTAL];

	ft_bzero(w, 64 * sizeof(uint32_t));
	init_word_array(chunk, w);
	init_sha_lvars(lvars, sha);
	compression_loop(lvars, w);
	change_hash_value((uint32_t *)(sha->vars), lvars);
}
