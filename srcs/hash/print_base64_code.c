#include "ft_ssl.h"

void		print_base64_code(const int fd,
			const char *code)
{
	size_t	length;
	size_t	i;
	size_t	chunks;

	length = ft_strlen(code);
	i = 0;
	chunks = length / 64;
	while (i < chunks)
	{
		write(fd, &(code[(i++) * 64]), 64);
		ft_putchar_fd('\n', fd);
	}
	if (length % 64)
	{
		write(fd, &(code[i * 64]), length % 64);
		ft_putchar_fd('\n', fd);
	}
}