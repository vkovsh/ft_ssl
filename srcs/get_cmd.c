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

static const char *g_hash_cmd[HASH_TOTAL] = MD_TXT;
static const char *g_cipher_cmd[CIPHER_TOTAL] = CIPHER_TXT;
static const char **g_cmd[TOTAL_CMD] =
	{g_hash_cmd, g_cipher_cmd};

int				get_cmd(const char *str,
				t_cmdtype cmdtype,
				int total)
{
	char		*upper;
	int			type;
	const char	**cmd = g_cmd[cmdtype];

	type = -1;
	upper = ft_strtoupper(str);
	while (++type < total)
		if (!ft_strcmp(upper, cmd[type]))
		{
			ft_strdel(&upper);
			return (type);
		}
	ft_strdel(&upper);
	return (-1);
}
