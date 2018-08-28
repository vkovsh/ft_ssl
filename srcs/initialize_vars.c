#include "ft_ssl.h"

uint32_t g_md_default[MD_VAR_TOTAL] = {
	0x67452301, 0xefcdab89,	0x98badcfe, 0x10325476};

uint32_t g_sha256_default[SHA_VAR_TOTAL] = {
	0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
	0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

uint32_t g_sha224_default[SHA_VAR_TOTAL] = {
	0xc1059ed8, 0x367cd507, 0x3070dd17, 0xf70e5939,
	0xffc00b31, 0x68581511, 0x64f98fa7, 0xbefa4fa4};

uint64_t g_sha512_default[SHA_VAR_TOTAL] = {
	0x6a09e667f3bcc908, 0xbb67ae8584caa73b,
	0x3c6ef372fe94f82b, 0xa54ff53a5f1d36f1,
	0x510e527fade682d1, 0x9b05688c2b3e6c1f,
	0x1f83d9abfb41bd6b, 0x5be0cd19137e2179};

void *g_hash_defaults[HASH_TOTAL] = {
	g_md_default, g_sha256_default,
	g_sha224_default, g_sha512_default};

void			initialize_vars(t_container *c)
{
	c->vars = ft_memalloc(HASH_SIZES[c->hashtype]);
	ft_memmove(c->vars, g_hash_defaults[c->hashtype],
		HASH_SIZES[c->hashtype]);
}