#include "../minishell.h"

int	ft_pwd(t_all *all)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		ft_exit(errno, "getcwd", all);
	printf("%s\n", pwd);
	free(pwd);
	all->errnum = 0;
	return (0);
}
