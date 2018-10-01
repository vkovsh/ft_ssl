/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_padded_msg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 13:42:51 by vkovsh            #+#    #+#             */
/*   Updated: 2018/08/29 13:42:59 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		*create_padded_msg_md5(void *msg,
			size_t msg_len,
			size_t *new_msg_len)
{
	size_t	padded_size;
	uint8_t	*padded_msg;

	padded_size = msg_len + (64 - msg_len % 64);
	if (msg_len % 64 >= 54)
		padded_size += 64;
	*new_msg_len = padded_size;
	padded_msg = ft_memalloc(padded_size);
	ft_memmove(padded_msg, msg, msg_len);
	padded_msg[msg_len] = 0x80;
	msg_len <<= 3;
	padded_msg[padded_size - 8] = msg_len;
	padded_msg[padded_size - 7] = msg_len >> 8;
	padded_msg[padded_size - 6] = msg_len >> 16;
	padded_msg[padded_size - 5] = msg_len >> 24;
	return (padded_msg);
}

void		*create_padded_msg_sha2(void *msg,
			size_t msg_len,
			size_t *new_msg_len)
{
	size_t	padded_size;
	uint8_t	*padded_msg;

	padded_size = msg_len + (64 - msg_len % 64);
	if (msg_len % 64 >= 54)
		padded_size += 64;
	*new_msg_len = padded_size;
	padded_msg = ft_memalloc(padded_size);
	ft_memmove(padded_msg, msg, msg_len);
	padded_msg[msg_len] = 0x80;
	msg_len <<= 3;
	padded_msg[padded_size - 1] = msg_len;
	padded_msg[padded_size - 2] = msg_len >> 8;
	padded_msg[padded_size - 3] = msg_len >> 16;
	padded_msg[padded_size - 4] = msg_len >> 24;
	return (padded_msg);
}

void		*create_padded_msg_sha512(void *msg,
			size_t msg_len,
			size_t *new_msg_len)
{
	size_t	padded_size;
	uint8_t	*padded_msg;

	padded_size = msg_len + (128 - msg_len % 128);
	if (msg_len % 128 >= 112)
		padded_size += 128;
	*new_msg_len = padded_size;
	padded_msg = ft_memalloc(padded_size);
	ft_memmove(padded_msg, msg, msg_len);
	padded_msg[msg_len] = 0x80;
	msg_len <<= 3;
	padded_msg[padded_size - 1] = msg_len;
	padded_msg[padded_size - 2] = msg_len >> 8;
	padded_msg[padded_size - 3] = msg_len >> 16;
	padded_msg[padded_size - 4] = msg_len >> 24;
	return (padded_msg);
}
