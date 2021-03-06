/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hash2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 13:53:04 by vkovsh            #+#    #+#             */
/*   Updated: 2018/08/29 13:53:05 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			ft_print_md5(t_container *hash)
{
	uint32_t	*v;

	reverse_md(hash);
	v = (uint32_t *)(hash->vars);
	ft_printf(g_format[hash->hashtype],
	v[A_MD], v[B_MD], v[C_MD], v[D_MD]);
}

void			ft_print_sha256(t_container *hash)
{
	uint32_t	*v;

	v = (uint32_t *)(hash->vars);
	ft_printf(g_format[hash->hashtype],
	v[H0], v[H1], v[H2], v[H3],
	v[H4], v[H5], v[H6], v[H7]);
}

void			ft_print_sha224(t_container *hash)
{
	uint32_t	*v;

	v = (uint32_t *)(hash->vars);
	ft_printf(g_format[hash->hashtype],
	v[H0], v[H1], v[H2], v[H3],
	v[H4], v[H5], v[H6]);
}

void			ft_print_sha512(t_container *hash)
{
	uint64_t	*v;

	v = (uint64_t *)(hash->vars);
	ft_printf(g_format[hash->hashtype],
	v[H0], v[H1], v[H2], v[H3],
	v[H4], v[H5], v[H6], v[H7]);
}
