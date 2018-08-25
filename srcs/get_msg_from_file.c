#include "ft_ssl.h"

char		*get_msg_from_file(const char *filename)
{
	int		fd;
	char	*line;
	char	*msg;

	line = NULL;
	msg = ft_strnew(0);
	if ((fd = open(filename, O_RDONLY)) < 0)
		return (NULL);
	while (get_next_line(fd, &line) > 0)
		msg = ft_strjoin_free(msg, line, TRUE, TRUE);
	if (close(fd) < 0)
		return (NULL);
	return (msg);
}

void		*get_stream(const int fd, void *buf,
			size_t buf_size)
{
	size_t	split;
	void	*stream;
	size_t	r;

	split = 0;
	stream = ft_memalloc(1);
	while ((r = read(fd, buf + split, buf_size - split)) > 0)
	{
		stream = ft_strjoin_free(stream,
					buf + split,
					TRUE, FALSE);
		split += r;
		if (split >= buf_size)
		{
			ft_bzero(buf, buf_size);
			split = 0;
		}
	}
	return (stream);
}