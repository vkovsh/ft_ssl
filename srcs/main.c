#include "ft_ssl.h"

int					main(int ac, char **av)
{ 
	t_md5			md;

	md = ft_md5hash(av[ac - 1]);
	ft_printf("%x%x%x%x\n",
		md.mdvars[A_VAR],
		md.mdvars[B_VAR],
		md.mdvars[C_VAR],
		md.mdvars[D_VAR]);
	return (0);
}