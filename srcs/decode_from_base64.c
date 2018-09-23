#include "ft_ssl.h"

static const uint8_t g_base64_values[123] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 62, 0, 0, 0, 63,
	52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 0, 0,
	0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6,
	7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18,
	19, 20, 21, 22, 23, 24, 25, 0, 0, 0, 0, 0,
	0, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36,
	37, 38, 39, 40, 41, 42, 43,	44, 45, 46, 47, 48,
	49, 50, 51};

static void		decode_trinity(const char *code,
				uint8_t *binary,
				int code_index,
				int bin_index)
{
	uint32_t	value;
	int			i;

	i = -1;
	value = 0;
	while (++i < 4)
		value |= 
			g_base64_values[(int)code[code_index + i]] <<
				(18 - i * 6);
	i = -1;
	while (++i < 3)
		binary[bin_index + i] = value >> (16 - i * 8);
}

uint8_t		*decode_from_base64(const char *code)
{
	size_t	code_length;
	size_t	bin_length;
	int		i;
	int		j;
	uint8_t	*binary;
	
	code_length = ft_strlen(code);
	bin_length = code_length - (code_length / 4);
	if (!(binary =
		(uint8_t *)malloc(sizeof(char) * bin_length)))
			return (NULL);
	i = -1;
	j = 0;
	while ((i += 4) < (int)code_length)
	{
		decode_trinity(code, binary, i - 3, j);
		j += 3;
	}
	return (binary);
}