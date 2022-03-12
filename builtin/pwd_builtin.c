#include "../minishell.h"

int	ft_pwd(t_all *all)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		err_exit(errno, "getcwd"); //, all);
	ft_putendl_fd(pwd, 1);
	free_null((void**)&pwd);
	all->errnum = 0;
	return (0);
}
