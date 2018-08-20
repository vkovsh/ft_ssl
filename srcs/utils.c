#include "ft_ssl.h"

unsigned char s_vars[S_LEN + 1] = S;
unsigned int k_vars_md[K_LEN] = {
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
unsigned int k_vars_sha[K_LEN] = {
	0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,
	0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
	0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,
	0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
	0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,
	0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
	0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,
	0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
	0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,
	0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
	0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,
	0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
	0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,
	0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
	0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,
	0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2};

void				initialize_md_vars(t_container *md)
{
	md->vars =
	(unsigned int *)malloc(sizeof(unsigned int) *
					MD_VAR_TOTAL);
	md->vars[A_VAR] = 0x67452301;
	md->vars[B_VAR] = 0xefcdab89;
	md->vars[C_VAR] = 0x98badcfe;
	md->vars[D_VAR] = 0x10325476;
}

void				initialize_sha_vars(t_container *sha)
{
	sha->vars =
	(unsigned int *)malloc(sizeof(unsigned int) *
					SHA_VAR_TOTAL);
	sha->vars[H_ZERO] = 0x6a09e667;
	sha->vars[H_ONE] = 0xbb67ae85;
	sha->vars[H_TWO] = 0x3c6ef372;
	sha->vars[H_THREE] = 0xa54ff53a;
	sha->vars[H_FOUR] = 0x510e527f;
	sha->vars[H_FIVE] = 0x9b05688c;
	sha->vars[H_SIX] = 0x1f83d9ab;
	sha->vars[H_SEVEN] = 0x5be0cd19;
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