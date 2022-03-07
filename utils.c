
#include "minishell.h"

int	ft_count_cmd(t_command *cmd) //+
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

int	ft_count_envp(t_env *envp) //+
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

void	ft_print_error(int errnum, char *str, char *cmd_name) //+
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

void	ft_make_array(t_env *envp, char **env, int len, t_all *all) //-
{
	int		i;
	char	*arr;

	i = 0;
	while (i < len)
	{
		env[i] = ft_strdup(envp->key); //, all);
		if (envp->separator)
		{
			arr = ft_strjoin(env[i], envp->separator, all);
			free(env[i]);
			env[i] = arr;
		}
		if (envp->value)
		{
			arr = ft_strjoin(env[i], envp->value, all);
			free(env[i]);
			env[i] = arr;
		}
		envp = envp->next;
		i++;
	}
	env[i] = NULL;
}

void	ft_env_list_to_array(t_env *envp, t_all *all) //+
{
	int		n;

	n = ft_count_envp(envp);
	all->env = (char **)malloc(sizeof(char *) * (n + 1));
	if (all->env == NULL)
		ft_exit(12, "malloc"); //, all);
	ft_make_array(envp, all->env, n, all);
}
