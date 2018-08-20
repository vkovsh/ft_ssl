#include "ft_ssl.h"

t_container				ft_sha2hash(char *msg)
{
	t_container			sha;
	void				*chunk;
	size_t				i;

	initialize_sha_vars(&sha);
	sha.padded_msg = create_padded_msg(msg,
				ft_strlen(msg),
				&sha.padded_msg_len);
	i = 0;
	chunk = ft_memalloc(64);
	while (i < sha.padded_msg_len)
	{
		ft_memmove(chunk, sha.padded_msg + i, 64);
		proceed_chunk_sha2(&sha, chunk);
		i += 64;
	}
	return (sha);			
}