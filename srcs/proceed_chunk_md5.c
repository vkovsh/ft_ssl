#include "ft_ssl.h"

static void				change_md_vars(
						uint32_t *dst,
						uint32_t *src)
{
	int				i;

	i = -1;
	while (++i < MD_VAR_TOTAL)
		dst[i] += src[i];
}

static void				set_f_g(uint32_t *f,
						uint32_t *g,
						uint32_t *t,
						int i)
{
	if (i <= 15)
	{
		*f = (t[B_MD] & t[C_MD]) | ((~t[B_MD]) & t[D_MD]);
		*g = i;
	}
	else if (i <= 31)
	{
		*f = (t[D_MD] & t[B_MD]) | ((~t[D_MD]) & t[C_MD]);
		*g = (5 * i + 1) % 16;
	}
	else if (i <= 47)
	{
		*f = t[B_MD] ^ t[C_MD] ^ t[D_MD];
		*g = (3 * i + 5) % 16;
	}
	else
	{
		*f = t[C_MD] ^ (t[B_MD] | (~t[D_MD]));
		*g = (7 * i) % 16;
	}
}

void					proceed_chunk_md5(t_container *md,
						uint8_t *chunk)
{
	uint32_t		t[MD_VAR_TOTAL];
	int					i;
	uint32_t		f;
	uint32_t		g;
	const uint32_t	*m = (const uint32_t *)chunk;

	ft_memmove(t, md->vars,
		sizeof(UINT32_MAX) * MD_VAR_TOTAL);
	i = -1;
	while (++i < 64)
	{
		set_f_g(&f, &g, t, i);
		f += t[A_MD] + g_kvars_md[i] + m[g];
        t[A_MD] = t[D_MD];
        t[D_MD] = t[C_MD];
        t[C_MD] = t[B_MD];
        t[B_MD] += LROT(f, g_svars[i], 32);
	}
	change_md_vars((uint32_t *)(md->vars), t);
}