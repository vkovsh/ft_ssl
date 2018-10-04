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

void				crypt_arg(const int read_fd,
					const int write_fd,
					uint16_t flags,
					t_hashtype htype)
{
	uint8_t			*binary;
	char			*code;
	char			buf[4096];

	ft_bzero(buf, 4096);
	if (htype == -1)
		exit(1);
	binary = (uint8_t *)get_stream(read_fd, buf, 4096);
	if ((flags & FLAG_E) || !(flags & FLAG_D))
	{
		code = encode_to_base64(binary,	ft_strlen((char *)binary));
		print_base64_code(write_fd, code);
	}
	else
	{
		code = (char *)decode_from_base64((char *)binary);
		ft_dprintf(write_fd, "%s", code);
	}
	free(code);
	free(binary);
}

void				proceed_args_for_hashing(const int ac,
					char **av, const int cmd)
{
	int				flags;
	int				i;

	flags = 0;
	i = 1;
	while (++i < ac && av[i][0] == '-')
		flags = append_flag(flags, av[i]);
	if (flags & FLAG_P || i == ac)
		handle_input_for_hash(flags, cmd);
	while (i++ < ac)
		hash_arg(flags, av[i - 1], cmd);
}

void				proceed_args_for_cipher(const int ac,
					char **av, const int cmd)
{
	char			*in;
	char			*out;
	int				flags;
	int				i;

	in = NULL;
	out = NULL;
	flags = 0;
	i = 1;
	while (++i < ac)
	{
		if (av[i][0] == '-')
			flags = append_flag(flags, av[i]);
		else if (flags & FLAG_I && !in)
			in = av[i];
		else if (flags & FLAG_O && !out)
			out = av[i];
	}
	int read_fd = (in) ? open(in, O_RDONLY) : 0;
	int write_fd = (out) ? open(out, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR) : 1;
	if (read_fd == -1 || write_fd == -1)
		exit(1);
	crypt_arg(read_fd, write_fd, flags, cmd);
	if (read_fd != 0)
		close(read_fd);
	if (write_fd != 1)
		close(write_fd);
}

int					main(int ac, char **av)
{
	int				cmd;

	initial_shuffle(1);
	char *pwd = get_pwd();
	if (pwd == NULL)
		exit(0);
	ft_printf("%s\n", pwd);
	ft_strdel(&pwd);
	exit(1);
	if (ac >= 2)
	{
		if ((cmd = get_cmd(av[1], HASH_CMD, HASH_TOTAL)) != -1)
			proceed_args_for_hashing(ac, av, cmd);
		else if ((cmd = get_cmd(av[1], CIPHER_CMD, CIPHER_TOTAL)) != -1)
			proceed_args_for_cipher(ac, av, cmd);
		else
			ft_info(av[1]);
	}
	else
		ft_printf(USG);
	return (0);
}
