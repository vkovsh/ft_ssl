#include "ft_ssl.h"

int					main(int ac, char **av)
{ 
	t_container		hash;
	char			*res;
	uint32_t	*vars; 

	if (ac > 2)
	{
		res = ft_strtoupper(av[1]);
		if (!ft_strcmp(res, "MD5"))
		{
			struct stat s;
			stat(av[ac - 1], &s);
			if (s.st_size > (UINT_MAX >> 3))
			{
				ft_printf("too big!\n");
				exit(0);
			}
			int fd = open(av[ac - 1], O_RDONLY);
			char *buf = ft_strnew(s.st_size);
			ft_bzero(buf, s.st_size);
			uint8_t *stream = get_stream(fd, buf, s.st_size);
			close(fd);
			free(buf);
			hash = ft_md5hash(stream, s.st_size);
			free(stream);
			vars = (uint32_t *)(hash.vars);
			ft_printf("MD5(%s)= %08x%08x%08x%08x\n",
			av[ac - 1],
			vars[A_MD], vars[B_MD],
			vars[C_MD], vars[D_MD]);
		}
		else if (!ft_strcmp(res, "SHA256"))
		{
			hash = ft_sha256hash(get_msg_from_file(av[ac - 1]));
			vars = (uint32_t *)(hash.vars);
			ft_printf("SHA256(%s)= %08x%08x%08x%08x%08x%08x%08x%08x\n",
				av[ac - 1],
				vars[H_ZERO], vars[H_ONE],
				vars[H_TWO], vars[H_THREE],
				vars[H_FOUR], vars[H_FIVE],
				vars[H_SIX], vars[H_SEVEN]);
		}
		else if (!ft_strcmp(res, "SHA224"))
		{
			hash = ft_sha224hash(get_msg_from_file(av[ac - 1]));
			vars = (uint32_t *)(hash.vars);
			ft_printf("SHA224(%s)= %08x%08x%08x%08x%08x%08x%08x\n",
				av[ac - 1],
				vars[H_ZERO], vars[H_ONE],
				vars[H_TWO], vars[H_THREE],
				vars[H_FOUR], vars[H_FIVE],
				vars[H_SIX]);
		}
		else if (!ft_strcmp(res, "SHA512"))
		{
			hash = ft_sha512hash(get_msg_from_file(av[ac - 1]));
			/*uint8_t *vars2 = (uint8_t *)(hash.vars);
			ft_printf("SHA512(%s)= ", av[ac - 1]);
			for (int i = 0; i < 8 * 8; ++i)
				ft_printf("%02x", *(vars2 + i));
			ft_printf("\n");*/
			uint64_t *v = (uint64_t *)(hash.vars);
			ft_printf("SHA512(%s)= %.16llx%.16llx%.16llx%.16llx%.16llx%.16llx%.16llx%.16llx\n",
				av[ac - 1],
				v[H_ZERO], v[H_ONE],
				v[H_TWO], v[H_THREE],
				v[H_FOUR], v[H_FIVE],
				v[H_SIX], v[H_SEVEN]);
		}
		else
			ft_printf("Hash method undefined\n");
	}
	else
		ft_printf("Error\n");
	return (0);
}