/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proceed_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 14:42:37 by vkovsh            #+#    #+#             */
/*   Updated: 2018/08/29 14:42:39 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static bool			check_s_flag(uint8_t flags,
					char *txt, uint8_t **stream,
					size_t *size)
{
	if (flags & FLAG_S)
	{
		*stream = (uint8_t *)txt;
		*size = ft_strlen(txt);
	}
	else
	{
		if (!(*stream = get_file(txt, size)))
			return (false);
	}
	return (true);
}

void				proceed_q_r_def(uint8_t flags,
					t_container *hash,
					t_hashtype htype,
					char *txt)
{
	const char		*mdtxt[HASH_TOTAL] = MD_TXT;

	if (flags & FLAG_Q)
	{
		ft_print_hash(hash);
		ft_printf("\n");
	}
	else if (flags & FLAG_R)
	{
		ft_print_hash(hash);
		ft_printf(" *%s\n",
		flags & FLAG_STDIN ? "stdin" : txt);
	}
	else
	{
		ft_printf("%s(%s)= ", mdtxt[htype],
		flags & FLAG_STDIN ? "stdin" : txt);
		ft_print_hash(hash);
		ft_printf("\n");
	}
}

void				proceed_arg(uint8_t flags,
					char *txt,
					t_hashtype htype)
{
	uint8_t			*stream;
	size_t			size;
	t_container		hash;

	if (!check_s_flag(flags, txt, &stream, &size))
		return ;
	hash = ft_hash(stream, size, htype);
	if (flags & FLAG_P)
		write(1, stream, size);
	proceed_q_r_def(flags, &hash, htype, txt);
	free(hash.vars);
	free(hash.padded_msg);
}
