/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 13:44:21 by vkovsh            #+#    #+#             */
/*   Updated: 2018/08/29 13:44:23 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_print_md g_print_funcs[HASH_TOTAL] = {
	ft_print_md5, ft_print_sha256,
	ft_print_sha224, ft_print_sha512,
	ft_print_sha384, ft_print_sha512_256,
	ft_print_sha512_224};

const char *g_format[HASH_TOTAL] = {
	"%.8x%.8x%.8x%.8x",
	"%.8x%.8x%.8x%.8x%.8x%.8x%.8x%.8x",
	"%.8x%.8x%.8x%.8x%.8x%.8x%.8x",
	"%.16llx%.16llx%.16llx%.16llx%.16llx%.16llx%.16llx%.16llx",
	"%.16llx%.16llx%.16llx%.16llx%.16llx%.16llx",
	"%.16llx%.16llx%.16llx%.16llx",
	"%.16llx%.16llx%.16llx%.8llx"
};

void			ft_print_sha384(t_container *hash)
{
	uint64_t	*v;

	v = (uint64_t *)(hash->vars);
	ft_printf(g_format[hash->hashtype],
	v[H0], v[H1], v[H2], v[H3],
	v[H4], v[H5]);
}

void			ft_print_sha512_256(t_container *hash)
{
	uint64_t	*v;

	v = (uint64_t *)(hash->vars);
	ft_printf(g_format[hash->hashtype],
	v[H0], v[H1], v[H2], v[H3]);
}

void			ft_print_sha512_224(t_container *hash)
{
	uint64_t	*v;

	v = (uint64_t *)(hash->vars);
	ft_printf(g_format[hash->hashtype],
	v[H0], v[H1], v[H2], v[H3] >> 32);
}

void			ft_print_hash(t_container *hash)
{
	g_print_funcs[hash->hashtype](hash);
}
