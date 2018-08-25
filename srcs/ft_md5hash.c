#include "ft_ssl.h"

void					reverse_uint(
						uint8_t *val_addr)
{
	uint8_t		tmp;

	tmp = val_addr[0];
	val_addr[0] = val_addr[3];
	val_addr[3] = tmp;
	tmp = val_addr[1];
	val_addr[1] = val_addr[2];
	val_addr[2] = tmp;
}

void					reverse_uint64(
						uint8_t *val_addr)
{
	uint8_t		tmp;

	tmp = val_addr[0];
	val_addr[0] = val_addr[7];
	val_addr[7] = tmp;

	tmp = val_addr[1];
	val_addr[1] = val_addr[6];
	val_addr[6] = tmp;

	tmp = val_addr[2];
	val_addr[2] = val_addr[5];
	val_addr[5] = tmp;

	tmp = val_addr[3];
	val_addr[3] = val_addr[4];
	val_addr[4] = tmp;
}

void					reverse_md(t_container *md)
{
	int					i;
	uint8_t		*val_addr;

	i = -1;
	while (++i < MD_VAR_TOTAL)
	{
		val_addr = (uint8_t *)&(((uint32_t *)(md->vars))[i]);
		reverse_uint(val_addr);
	}
}

t_container				ft_md5hash(uint8_t *msg,
						size_t len)
{
	t_container			md;
	size_t				i;

	initialize_md_vars(&md);
	md.padded_msg = create_padded_msg_md5(msg,
				len,
				&md.padded_msg_len);
	i = 0;
	while (i < md.padded_msg_len)
	{
		proceed_chunk_md5(&md, md.padded_msg + i);
		i += 64;
	}
	reverse_md(&md);
	return (md);			
}