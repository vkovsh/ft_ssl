/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_flag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 14:36:29 by vkovsh            #+#    #+#             */
/*   Updated: 2018/08/29 14:36:31 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint8_t				append_flag(uint8_t flag,
					const char *str)
{
	int				i;
	int				j;
	uint8_t			new_flag;
	const char		flags_ssl[] = "pqrsioedakv";

	i = 0;
	new_flag = flag;
	while (str[++i])
	{
		if (!ft_isalnum(str[i]))
		{
			ft_printf("%s '%c'\n", "ft_ssl: invalid option --", str[i]);
			exit(1);
		}
		else
		{
			j = -1;
			while (++j < FLAG_SSL_TOTAL)
				if (flags_ssl[j] == str[i])
					new_flag |= 1 << j;
		}
	}
	return (new_flag);
}
