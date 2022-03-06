
#include "minishell.h"

int	ft_count_cmd(t_command *cmd)
{
	int	res;

	if (!cmd->cmd[0])
		return (0);
	res = 0;
	while (cmd)
	{
		res++;
		cmd = cmd->next;
	}
	return (res);
}

int	ft_count_envp(t_env *envp)
{
	int	res;

	res = 0;
	while (envp)
	{
		res++;
		envp = envp->next;
	}
	return (res);
}

void	ft_print_error(int errnum, char *str, char *cmd_name)
{
	char	*errmsg;

	errmsg = strerror(errnum);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_name, 2);
	write(2, ": ", 3);
	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, ": ", 3);
	}
	write(2, errmsg, ft_strlen(errmsg));
	write(2, "\n", 1);
}

void	ft_make_array(t_env *envp, char **env, int len, t_all *all)
{
	int		i;
	char	*arr;

	(void)all;
	i = -1;
	while (++i < len)
	{
		env[i] = ft_strdup(envp->key, all);
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
	}
	env[i] = NULL;
}

void	ft_env_list_to_array(t_env *envp, t_all *all)
{
	int		len;

	len = ft_count_envp(envp);
	all->env = malloc(sizeof(char *) * (len + 1));
	if (!all->env)
		ft_exit(12, "malloc", all);
	ft_make_array(envp, all->env, len, all);
}
