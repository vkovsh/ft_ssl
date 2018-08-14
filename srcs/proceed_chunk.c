#include "ft_ssl.h"

static void			set_md_vars(t_md5 *dst, t_md5 *src)
{
	dst->mdvars[A_VAR] = src->mdvars[A_VAR];
	dst->mdvars[B_VAR] = src->mdvars[B_VAR];
	dst->mdvars[C_VAR] = src->mdvars[C_VAR];
	dst->mdvars[D_VAR] = src->mdvars[D_VAR];
}

static void			change_md_vars(t_md5 *dst, t_md5 *src)
{
	dst->mdvars[A_VAR] += src->mdvars[A_VAR];
	dst->mdvars[B_VAR] += src->mdvars[B_VAR];
	dst->mdvars[C_VAR] += src->mdvars[C_VAR];
	dst->mdvars[D_VAR] += src->mdvars[D_VAR];
}

void				set_f_g(unsigned int *f,
					unsigned int *g,
					t_md5 *tmp,
					int i)
{
	if (i <= 15)
	{
		*f = (tmp->mdvars[B_VAR] & tmp->mdvars[C_VAR]) |
		((~tmp->mdvars[B_VAR]) & tmp->mdvars[D_VAR]);
		*g = i;
	}
	else if (i <= 31)
	{
		*f = (tmp->mdvars[D_VAR] & tmp->mdvars[B_VAR]) |
		((~tmp->mdvars[D_VAR]) & tmp->mdvars[C_VAR]);
		*g = (5 * i + 1) % 16;
	}
	else if (i <= 47)
	{
		*f = tmp->mdvars[B_VAR] ^ tmp->mdvars[C_VAR] ^
		tmp->mdvars[D_VAR];
		*g = (3 * i + 5) % 16;
	}
	else
	{
		*f = tmp->mdvars[C_VAR] ^ (tmp->mdvars[B_VAR] |
		(~tmp->mdvars[D_VAR]));
		*g = (7 * i) % 16;
	}
}

void				proceed_chunk(t_md5 *md,
					unsigned char *chunk)
{
	t_md5			tmp;
	int				i;
	unsigned int	f;
	unsigned int	g;

	set_md_vars(&tmp, md);
	i = -1;
	while (++i < 64)
	{
		set_f_g(&f, &g, &tmp, i);
		f += tmp.mdvars[A_VAR] + k_vars[i] + get_m(chunk, g);
        tmp.mdvars[A_VAR] = tmp.mdvars[D_VAR];
        tmp.mdvars[D_VAR] = tmp.mdvars[C_VAR];
        tmp.mdvars[C_VAR] = tmp.mdvars[B_VAR];
        tmp.mdvars[B_VAR] += leftrotate(f, s_vars[i]);
	}
	change_md_vars(md, &tmp);
}