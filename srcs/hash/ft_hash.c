/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 13:43:41 by vkovsh            #+#    #+#             */
/*   Updated: 2018/08/29 13:43:43 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_container			ft_hash(uint8_t *msg,
					size_t len,
					t_hashtype htype)
{
	t_container		c;
	size_t			i;
	const uint8_t	chunk_sizes[HASH_TOTAL] =
				{64, 64, 64, 128, 128, 128, 128};

	c.hashtype = htype;
	initialize_vars(&c);
	c.padded_msg = g_cr_padd_funcs[c.hashtype](msg,
					len, &c.padded_msg_len);
	i = 0;
	while (i < c.padded_msg_len)
	{
		g_chunkfuncs[c.hashtype](&c, c.padded_msg + i);
		i += chunk_sizes[c.hashtype];
	}
	return (c);
}
