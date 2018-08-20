#include "ft_ssl.h"

t_container				ft_md5hash(char *msg)
{
	t_container			md;
	void				*chunk;
	size_t				i;

	initialize_md_vars(&md);
	md.padded_msg = create_padded_msg(msg,
				ft_strlen(msg),
				&md.padded_msg_len);
	i = 0;
	chunk = ft_memalloc(64);
	while (i < md.padded_msg_len)
	{
		ft_memmove(chunk, md.padded_msg + i, 64);
		proceed_chunk_md5(&md, chunk);
		i += 64;
	}
	return (md);			
}