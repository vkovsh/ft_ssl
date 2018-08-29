/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 13:43:52 by vkovsh            #+#    #+#             */
/*   Updated: 2018/08/29 13:43:55 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint8_t				*get_file(const char *path, size_t *size)
{
	struct stat		s;
	uint8_t			*stream;
	int				fd;
	uint8_t			*to_del;

	if (stat(path, &s) < 0 ||
		(fd = open(path, O_RDONLY)) < 0)
	{
		ft_printf(NO_FILE, path);
		return (NULL);
	}
	stream = ft_memalloc(s.st_size);
	to_del = stream;
	stream = get_stream(fd, stream, s.st_size);
	free(to_del);
	if (close(fd) < 0)
		return (NULL);
	*size = s.st_size;
	return (stream);
}

void				handle_input(uint8_t flags,
					t_hashtype htype)
{
	char			*line;
	char			buf[4096];

	ft_bzero(buf, 4096);
	if (flags & FLAG_I)
	{
		while (get_next_line(0, &line))
		{
			proceed_arg(flags, line, htype);
			free(line);
		}
	}
	else
	{
		flags |= FLAG_STDIN;
		flags |= FLAG_S;
		line = get_stream(0, buf, 4096);
		proceed_arg(flags, line, htype);
		free(line);
	}
}

int					main(int ac, char **av)
{
	t_hashtype		htype;
	uint8_t			flags;
	int				i;

	if (ac >= 2)
	{
		if ((htype = get_md_cmd(av[1])) == UNDEFINED)
			ft_info(av[1]);
		flags = 0;
		i = 1;
		while (++i < ac && av[i][0] == '-')
			flags = append_flag(flags, av[i]);
		if (flags & FLAG_P || i == ac)
			handle_input(flags, htype);
		while (i++ < ac)
			proceed_arg(flags, av[i - 1], htype);
	}
	else
		ft_printf(USG);
	return (0);
}
