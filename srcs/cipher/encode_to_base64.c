#include "ft_ssl.h"

static void		encode_trinity(char *code,
				int *index,
				uint32_t trinity)
{
	int			i;

	i = 2;
	while ((i += 6) <= 26)
		code[++(*index)] = BASE64_TRANSFORM[(trinity << i) >> 26];
}

static uint32_t	init_trinity(const uint8_t a,
				const uint8_t b,
				const uint8_t c)
{
	uint32_t	trinity;

	trinity = c;
	trinity |= b << 8;
	trinity |= a << 16;
	return (trinity);
}

char			*encode_to_base64(const uint8_t *bin,
				size_t length)
{
	size_t		code_sz;
	char		*code;
	int			i;
	int			j;

	code_sz = length + ((float)length / 3);
	code_sz += (code_sz % 4) ? 4 - (code_sz % 4) + 1 : 1;
	if (!(code = (char *)malloc(code_sz * sizeof(char))))
		return (NULL);
	i = -3;
	j = -1;
	while ((i += 3) + 2 < (int)length)
		encode_trinity(code, &j,
			init_trinity(bin[i], bin[i + 1], bin[i + 2]));
	if (i < (int)length)
		encode_trinity(code, &j, init_trinity(bin[i],
			(i + 1 < (int)length) ? bin[i + 1] : 0, 0));
	code[++j] = '\0';
	while (code[--j] == 'A' && j > (int)length)
		code[j] = '=';
	return (code);
}