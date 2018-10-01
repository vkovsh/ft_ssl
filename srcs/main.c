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

void				handle_input_for_hash(uint16_t flags,
					t_hashtype htype)
{
	char			*line;
	char			buf[4096];

	ft_bzero(buf, 4096);
	if (flags & FLAG_I)
	{
		while (get_next_line(0, &line))
		{
			hash_arg(flags, line, htype);
			free(line);
		}
	}
	else
	{
		flags |= FLAG_STDIN;
		flags |= FLAG_S;
		line = get_stream(0, buf, 4096);
		hash_arg(flags, line, htype);
		free(line);
	}
}

void				handle_input_for_cipher(uint16_t flags,
					t_hashtype htype)
{
	uint8_t			*binary;
	char			*code;
	char			buf[4096];

	ft_bzero(buf, 4096);
	if (flags == 200 || htype == -1)
		exit(1);
	binary = (uint8_t *)get_stream(STDIN, buf, 4096);
	if ((flags & FLAG_E) || !(flags & FLAG_D))
	{
		code = encode_to_base64(binary,
			ft_strlen((char *)binary));
		print_base64_code(code);
	}
	else
	{
		code = (char *)decode_from_base64((char *)binary);
		ft_printf("%s\n", code);
	}
	free(code);
	free(binary);
}

int					main(int ac, char **av)
{
	int				cmd;
	uint16_t		flags;
	int				i;

	if (ac >= 2)
	{
		flags = 0;
		i = 1;
		if ((cmd = get_cmd(av[1], HASH_CMD, HASH_TOTAL)) != -1)
		{
			while (++i < ac && av[i][0] == '-')
				flags = append_flag(flags, av[i]);
			if (flags & FLAG_P || i == ac)
				handle_input_for_hash(flags, cmd);
			while (i++ < ac)
				hash_arg(flags, av[i - 1], cmd);
		}
		else if ((cmd = get_cmd(av[1], CIPHER_CMD, CIPHER_TOTAL)) != -1)
		{
			while (++i < ac && av[i][0] == '-')
				flags = append_flag(flags, av[i]);
			if ((flags & FLAG_D) && (flags & FLAG_E))
				exit(1);
			if (flags & FLAG_P || i == ac)
				handle_input_for_cipher(flags, cmd);
			/*while (i++ < ac)
			{
				if (flags & FLAG_E)
				{
					char *tmp = encode_to_base64((uint8_t *)(av[i - 1]),
							ft_strlen(av[i - 1]));
					ft_printf("%s\n", tmp);
					ft_strdel(&tmp);
				}
			}*/
		}
		else
			ft_info(av[1]);
	}
	else
		ft_printf(USG);
	return (0);
}
