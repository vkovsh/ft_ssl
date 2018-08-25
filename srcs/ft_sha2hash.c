#include "ft_ssl.h"

t_container				ft_sha256hash(char *msg)
{
	t_container			sha;
	void				*chunk;
	size_t				i;

	initialize_sha256_vars(&sha);
	sha.padded_msg = create_padded_msg_sha2(msg,
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

t_container				ft_sha224hash(char *msg)
{
	t_container			sha;
	void				*chunk;
	size_t				i;

	initialize_sha224_vars(&sha);
	sha.padded_msg = create_padded_msg_sha2(msg,
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

t_container				ft_sha512hash(char *msg)
{
	t_container			sha;
	void				*chunk;
	size_t				i;

	initialize_sha512_vars(&sha);
	sha.padded_msg = create_padded_msg_sha512(msg,
				ft_strlen(msg),
				&sha.padded_msg_len);
	i = 0;
	chunk = ft_memalloc(128);
	while (i < sha.padded_msg_len)
	{
		ft_memmove(chunk, sha.padded_msg + i, 128);
		proceed_chunk_sha512(&sha, chunk);
		i += 128;
	}
	return (sha);			
}