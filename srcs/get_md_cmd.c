/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_md_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 14:28:52 by vkovsh            #+#    #+#             */
/*   Updated: 2018/08/29 14:28:53 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_hashtype			get_md_cmd(const char *str)
{
	char			*upper;
	t_hashtype		htype;

	htype = UNDEFINED;
	upper = ft_strtoupper(str);
	if (!ft_strcmp(upper, "MD5"))
		htype = HASH_MD_FIVE;
	else if (!ft_strcmp(upper, "SHA256"))
		htype = HASH_SHA256;
	else if (!ft_strcmp(upper, "SHA224"))
		htype = HASH_SHA224;
	else if (!ft_strcmp(upper, "SHA512"))
		htype = HASH_SHA512;
	else if (!ft_strcmp(upper, "SHA384"))
		htype = HASH_SHA384;
	else if (!ft_strcmp(upper, "SHA512/256"))
		htype = HASH_SHA512_256;
	else if (!ft_strcmp(upper, "SHA512/224"))
		htype = HASH_SHA512_224;
	ft_strdel(&upper);
	return (htype);
}
