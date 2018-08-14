#include "ft_ssl.h"

unsigned char s_vars[S_LEN + 1] = S;
unsigned int k_vars[K_LEN] = {
	0xd76aa478,0xe8c7b756,0x242070db,0xc1bdceee,
	0xf57c0faf,0x4787c62a,0xa8304613,0xfd469501,
	0x698098d8,0x8b44f7af,0xffff5bb1,0x895cd7be,
	0x6b901122,0xfd987193,0xa679438e,0x49b40821,
	0xf61e2562,0xc040b340,0x265e5a51,0xe9b6c7aa,
	0xd62f105d,0x02441453,0xd8a1e681,0xe7d3fbc8,
	0x21e1cde6,0xc33707d6,0xf4d50d87,0x455a14ed,
	0xa9e3e905,0xfcefa3f8,0x676f02d9,0x8d2a4c8a,
	0xfffa3942,0x8771f681,0x6d9d6122,0xfde5380c,
	0xa4beea44,0x4bdecfa9,0xf6bb4b60,0xbebfbc70,
	0x289b7ec6,0xeaa127fa,0xd4ef3085,0x04881d05,
	0xd9d4d039,0xe6db99e5,0x1fa27cf8,0xc4ac5665,
	0xf4292244,0x432aff97,0xab9423a7,0xfc93a039,
	0x655b59c3,0x8f0ccc92,0xffeff47d,0x85845dd1,
	0x6fa87e4f,0xfe2ce6e0,0xa3014314,0x4e0811a1,
	0xf7537e82,0xbd3af235,0x2ad7d2bb,0xeb86d391};

void				initialize_md_vars(t_md5 *md)
{
	md->mdvars[A_VAR] = 0x67452301;
	md->mdvars[B_VAR] = 0xefcdab89;
	md->mdvars[C_VAR] = 0x98badcfe;
	md->mdvars[D_VAR] = 0x10325476;
}

void				*create_padded_msg(void *msg,
					size_t msg_len,
					size_t *new_msg_len)
{
	size_t	padded_size;
	char	*padded_msg;

	padded_size = msg_len + (64 - msg_len % 64);
	if (msg_len % 64 >= 54)
		padded_size += 64;
	padded_msg = ft_memalloc(padded_size);
	ft_memmove(padded_msg, msg, msg_len);
	padded_msg[msg_len] = 0x80;
	padded_msg[padded_size - 1] = msg_len;
	padded_msg[padded_size - 2] = msg_len >> 8;
	padded_msg[padded_size - 3] = msg_len >> 16;
	padded_msg[padded_size - 4] = msg_len >> 24;
	*new_msg_len = padded_size;
	return (padded_msg);
}

unsigned int		get_m(unsigned char *chunk, int g)
{
	unsigned int	m;
	unsigned char	*m_adress;
	int				split;

	m_adress = (unsigned char *)(&m);
	split = g << 2;
	m_adress[0] = chunk[split + 3];
	m_adress[1] = chunk[split + 2];
	m_adress[2] = chunk[split + 1];
	m_adress[3] = chunk[split];
	return (m);
}

unsigned int		leftrotate(unsigned int x, int c)
{
    return ((x << c) | (x >> (32 - c)));
}
