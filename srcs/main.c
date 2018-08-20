#include "ft_ssl.h"

int					main(int ac, char **av)
{ 
	t_container		hash;

	if (ac > 2)
	{
		if (!ft_strcmp(av[1], "md5") ||
			!ft_strcmp(av[1], "MD5"))
		{
			hash = ft_md5hash(av[ac - 1]);
			ft_printf("%x%x%x%x\n",
				hash.vars[A_VAR],
				hash.vars[B_VAR],
				hash.vars[C_VAR],
				hash.vars[D_VAR]);
		}
		else if (!ft_strcmp(av[1], "sha256") ||
				!ft_strcmp(av[1], "sha2") ||
				!ft_strcmp(av[1], "SHA2") ||
				!ft_strcmp(av[1], "SHA256"))
		{
			hash = ft_sha2hash(av[ac - 1]);
			ft_printf("%x%x%x%x%x%x%x%x\n",
				hash.vars[H_ZERO],
				hash.vars[H_ONE],
				hash.vars[H_TWO],
				hash.vars[H_THREE],
				hash.vars[H_FOUR],
				hash.vars[H_FIVE],
				hash.vars[H_SIX],
				hash.vars[H_SEVEN]);
		}
		else
			ft_printf("Error\n");
	}
	else
		ft_printf("Error\n");
	return (0);
}