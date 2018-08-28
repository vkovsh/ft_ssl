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
	ft_strdel(&upper);
	return (htype);
}

uint8_t				append_flag(uint8_t flag,
					const char *str)
{
	int				i;
	int				j;
	uint8_t			new_flag;

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
			{
				if (FLAGS_SSL[j] == str[i])
					new_flag |= 1 << j;
			}
		}
	}
	return (new_flag);
}

uint8_t				*get_file(const char *path, size_t *size)
{
	struct stat		s;
	uint8_t			*stream;
	int				fd;
	uint8_t			*to_del;

	if (stat(path, &s) < 0 ||
		(fd = open(path, O_RDONLY)) < 0)
	{
		ft_printf("'%s': No such file or directory\n", path);
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

void				proceed_arg(uint8_t flags,
					char *txt,
					t_hashtype htype)
{
	const char		*mdtxt[HASH_TOTAL] = MD_TXT;
	uint8_t			*stream;
	size_t			size;
	t_container		hash;

	if (flags & FLAG_S)
	{
		stream = (uint8_t *)txt;
		size = ft_strlen(txt);
	}
	else
	{
		if (!(stream = get_file(txt, &size)))
			return ;
	}
	hash = ft_hash(stream, size, htype);
	if (flags & FLAG_P)
		write(1, stream, size);
	if (flags & FLAG_Q)
	{
		ft_print_hash(&hash);
		ft_printf("\n");
	}
	else if (flags & FLAG_R)
	{
		ft_print_hash(&hash);
		ft_printf(" *%s\n", flags & FLAG_STDIN ? "stdin" : txt);
	}
	else
	{
		ft_printf("%s(%s)= ", mdtxt[htype], flags & FLAG_STDIN ? "stdin" : txt);
		ft_print_hash(&hash);
		ft_printf("\n");
	}
}

void				ft_info(const char *cmd)
{
	ft_printf("ft_ssl: Error: '%s' is an invalid command\n", cmd);
	ft_printf("Standard commands\n(in progress)\n\n");
	ft_printf("Message Digest commands\n");
	ft_printf("%-7s%-10s%-10s%-10s\n\n", "md5", "sha224", "sha256", "sha512");
	ft_printf("Cipher commands\n(in progress)\n");
	exit(1);
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
		if (i == ac)
		{
			if (flags & FLAG_I)
			{
				char *line;
				while (get_next_line(0, &line))
					proceed_arg(flags, line, htype);
			}
			else
			{
				flags |= FLAG_STDIN;
				flags |= FLAG_S;
				char buf[32];
				char *line = get_stream(0, buf, 32);
				proceed_arg(flags, line, htype);
			}
		}
		while (i++ < ac)
			proceed_arg(flags, av[i - 1], htype);
	}
	else
		ft_printf("usage: ft_ssl command [command opts] [command args]\n");
	return (0);
}