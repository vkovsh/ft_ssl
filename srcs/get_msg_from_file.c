/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_msg_from_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 13:44:53 by vkovsh            #+#    #+#             */
/*   Updated: 2018/08/29 13:44:55 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		*get_stream(const int fd, void *buf,
			size_t buf_size)
{
	size_t	split;
	void	*stream;
	size_t	r;

	split = 0;
	stream = ft_memalloc(1);
	while ((r = read(fd, buf + split, buf_size - split)) > 0)
	{
		stream = ft_strjoin_free(stream,
					buf + split,
					TRUE, FALSE);
		split += r;
		if (split >= buf_size)
		{
			ft_bzero(buf, buf_size);
			split = 0;
		}
	}
	return (stream);
}
