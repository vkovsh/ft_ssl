#include "ft_ssl.h"

char		*get_pwd(void)
{
	char	passbuf[1024];
	char	confirm_passbuf[1024];

	if (!readpassphrase("enter des-cbc encryption password: ",
			passbuf, sizeof(passbuf), RPP_REQUIRE_TTY))
		exit(1);
	if (!readpassphrase("Verifying - enter des-cbc encryption password: ",
			confirm_passbuf, sizeof(confirm_passbuf),
			RPP_REQUIRE_TTY))
		exit(1);
	if (!ft_strcmp(passbuf, confirm_passbuf))
		return (ft_strdup(passbuf));
	ft_printf("Verify failure\n");
	return (NULL);
}