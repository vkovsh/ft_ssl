#include "ft_ssl.h"

void			initialize_md_vars(t_container *md)
{
	uint32_t	*vars;

	md->vars = malloc(sizeof(uint32_t) * MD_VAR_TOTAL);
	vars = (uint32_t *)(md->vars);
	vars[A_MD] = 0x67452301;
	vars[B_MD] = 0xefcdab89;
	vars[C_MD] = 0x98badcfe;
	vars[D_MD] = 0x10325476;
}

void			initialize_sha256_vars(t_container *sha)
{
	uint32_t	*vars;
	
	sha->vars = malloc(sizeof(uint32_t) * SHA_VAR_TOTAL);
	vars = (uint32_t *)(sha->vars);
	vars[H_ZERO] = 0x6a09e667;
	vars[H_ONE] = 0xbb67ae85;
	vars[H_TWO] = 0x3c6ef372;
	vars[H_THREE] = 0xa54ff53a;
	vars[H_FOUR] = 0x510e527f;
	vars[H_FIVE] = 0x9b05688c;
	vars[H_SIX] = 0x1f83d9ab;
	vars[H_SEVEN] = 0x5be0cd19;
}

void			initialize_sha224_vars(t_container *sha)
{
	uint32_t	*vars;

	sha->vars = malloc(sizeof(uint32_t) * SHA_VAR_TOTAL);	
	vars = (uint32_t *)(sha->vars);
	vars[H_ZERO] = 0xc1059ed8;
	vars[H_ONE] = 0x367cd507;
	vars[H_TWO] = 0x3070dd17;
	vars[H_THREE] = 0xf70e5939;
	vars[H_FOUR] = 0xffc00b31;
	vars[H_FIVE] = 0x68581511;
	vars[H_SIX] = 0x64f98fa7;
	vars[H_SEVEN] = 0xbefa4fa4;
}

void			initialize_sha512_vars(t_container *sha)
{
	uint64_t	*vars;

	sha->vars = malloc(sizeof(uint64_t) * SHA_VAR_TOTAL);
	vars = (uint64_t *)(sha->vars);
	vars[H_ZERO] = 0x6a09e667f3bcc908;
	vars[H_ONE] = 0xbb67ae8584caa73b;
	vars[H_TWO] = 0x3c6ef372fe94f82b;
	vars[H_THREE] = 0xa54ff53a5f1d36f1;
	vars[H_FOUR] = 0x510e527fade682d1;
	vars[H_FIVE] = 0x9b05688c2b3e6c1f;
	vars[H_SIX] = 0x1f83d9abfb41bd6b;
	vars[H_SEVEN] = 0x5be0cd19137e2179;
}