#include "ft_ssl.h"
#include <termios.h>
#include <errno.h>

char			*get_pwd(void)
{
	char		*passbuf;
	char		*confirm_passbuf;
	t_termios	term;
	int			res;

	res = tcgetattr(0, &term);
	if (res == -1 )
	{
	    ft_printf("%s\n", strerror(errno));
	    exit(1);
    }
	ft_printf("enter des-cbc encryption password: ");
	term.c_lflag &= ~ECHO;
	tcsetattr(0, TCSAFLUSH, &term);
	get_next_line(0, &passbuf);
	ft_printf("\n");
	ft_printf("Verifying - enter des-cbc encryption password: ");
	get_next_line(0, &confirm_passbuf);
	ft_printf("\n");
	term.c_lflag |= ECHO;
	tcsetattr(0, TCSAFLUSH, &term);
	if (!ft_strcmp(passbuf, confirm_passbuf))
		return (ft_strdup(passbuf));
	ft_printf("Verify failure\n");
	free(passbuf);
	free(confirm_passbuf);
	return (NULL);
}