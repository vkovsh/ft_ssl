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

uint64_t g_sha384_default[SHA_VAR_TOTAL] = {
	0xCBBB9D5DC1059ED8, 0x629A292A367CD507,
	0x9159015A3070DD17, 0x152FECD8F70E5939,
	0x67332667FFC00B31, 0x8EB44A8768581511,
	0xDB0C2E0D64F98FA7, 0x47B5481DBEFA4FA4};

uint64_t g_sha512_256_default[SHA_VAR_TOTAL] = {
	0x22312194FC2BF72C, 0x9F555FA3C84C64C2,
	0x2393B86B6F53B151, 0x963877195940EABD,
	0x96283EE2A88EFFE3, 0xBE5E1E2553863992,
	0x2B0199FC2C85B8AA, 0x0EB72DDC81C52CA2};

uint64_t g_sha512_224_default[SHA_VAR_TOTAL] = {
	0x8C3D37C819544DA2, 0x73E1996689DCD4D6,
	0x1DFAB7AE32FF9C82, 0x679DD514582F9FCF,
	0x0F6D2B697BD44DA8, 0x77E36F7304C48942,
	0x3F9D85A86A1D36C8, 0x1112E6AD91D692A1};

void *g_hash_defaults[HASH_TOTAL] = {
	g_md_default, g_sha256_default,
	g_sha224_default, g_sha512_default,
	g_sha384_default, g_sha512_256_default,
	g_sha512_224_default};

void			initialize_vars(t_container *c)
{
	c->vars = ft_memalloc(HASH_SIZES[c->hashtype]);
	ft_memmove(c->vars, g_hash_defaults[c->hashtype],
		HASH_SIZES[c->hashtype]);
}