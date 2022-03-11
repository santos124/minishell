
#include "minishell.h"

int	count_cmd(t_cmd *cmd) //+
{
	int	i;

	if (!cmd->cmd[0])
		return (0);
	i = 0;
	while (cmd)
	{
		cmd = cmd->next;
		i++;
	}
	return (i);
}

int	count_env(t_env *envp) //+
{
	int	i;

	i = 0;
	while (envp)
	{
		envp = envp->next;
		i++;
	}
	return (i);
}

void	print_error(int errnum, char *str, char *cmd_name) //+
{
	char	*error;

	error = strerror(errnum);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_name, 2);
	ft_putstr_fd(": ", 2);
	if (str)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);

}

void	new_arr(t_env *envp, char **env, int len) //+
{
	int		i;
	char	*arr;

	i = 0;
	while (i < len)
	{
		env[i] = ft_strdup(envp->key);
		if (envp->sep)
		{
			arr = ft_strjoin(env[i], envp->sep);
			free_null((void**)&env[i]);
			env[i] = arr;
		}
		if (envp->val)
		{
			arr = ft_strjoin(env[i], envp->val);
			free_null((void**)&env[i]);
			env[i] = arr;
		}
		envp = envp->next;
		i++;
	}
	env[i] = NULL;
}

void	env_to_arr(t_env *envp, t_all *all) //+
{
	int		n;

	n = count_env(envp);
	all->env = (char **)malloc(sizeof(char *) * (n + 1));
	if (all->env == NULL)
		err_exit(12, "malloc"); //, all);
	new_arr(envp, all->env, n);
}
