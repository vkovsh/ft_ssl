#include "ft_ssl.h"

static void			set_md_vars(unsigned int *dst,
					t_container *src)
{
	dst[A_VAR] = src->vars[A_VAR];
	dst[B_VAR] = src->vars[B_VAR];
	dst[C_VAR] = src->vars[C_VAR];
	dst[D_VAR] = src->vars[D_VAR];
}

static void			change_md_vars(t_container *dst,
					unsigned int *src)
{
	dst->vars[A_VAR] += src[A_VAR];
	dst->vars[B_VAR] += src[B_VAR];
	dst->vars[C_VAR] += src[C_VAR];
	dst->vars[D_VAR] += src[D_VAR];
}

void				set_f_g(unsigned int *f,
					unsigned int *g,
					unsigned int *t,
					int i)
{
	if (i <= 15)
	{
		*f = (t[B_VAR] & t[C_VAR]) | ((~t[B_VAR]) & t[D_VAR]);
		*g = i;
	}
	else if (i <= 31)
	{
		*f = (t[D_VAR] & t[B_VAR]) | ((~t[D_VAR]) & t[C_VAR]);
		*g = (5 * i + 1) % 16;
	}
	else if (i <= 47)
	{
		*f = t[B_VAR] ^ t[C_VAR] ^ t[D_VAR];
		*g = (3 * i + 5) % 16;
	}
	else
	{
		*f = t[C_VAR] ^ (t[B_VAR] | (~t[D_VAR]));
		*g = (7 * i) % 16;
	}
}

void				proceed_chunk_md5(t_container *md,
					unsigned char *chunk)
{
	unsigned int	t[MD_VAR_TOTAL];
	int				i;
	unsigned int	f;
	unsigned int	g;

	set_md_vars(t, md);
	i = -1;
	while (++i < 64)
	{
		set_f_g(&f, &g, t, i);
		f += t[A_VAR] + k_vars_md[i] + get_m(chunk, g);
        t[A_VAR] = t[D_VAR];
        t[D_VAR] = t[C_VAR];
        t[C_VAR] = t[B_VAR];
        t[B_VAR] += lrot(f, s_vars[i]);
	}
	change_md_vars(md, t);
}