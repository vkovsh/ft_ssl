#include "ft_ssl.h"

void				crypt_arg(const int read_fd,
					const int write_fd,
					const uint16_t flags,
					const t_ciphertype cipher_type)
{
	uint8_t			*binary;
	uint8_t			*cipher;
	char			buf[4096];

	ft_bzero(buf, 4096);
	if (cipher_type == CIPHER_UNDEFINED)
		exit(1);
	binary = (uint8_t *)get_stream(read_fd, buf, 4096);
	if ((flags & FLAG_E) || !(flags & FLAG_D))
	{
		cipher = (uint8_t *)encode_to_base64(binary, ft_strlen((char *)binary));
		print_base64_code(write_fd, (char *)cipher);
	}
	else
	{
		cipher = decode_from_base64((char *)binary);
		ft_dprintf(write_fd, "%s", cipher);
	}
	free(cipher);
	free(binary);
}
