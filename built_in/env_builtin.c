#include "../minishell.h"

int	ft_check_path(t_all *all, char *cmd)
{
	t_env	*tmp;

	tmp = all->envp;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "PATH"))
			return (0);
		tmp = tmp->next;
	}
	all->errnum = 127;
	ft_print_error(2, NULL, cmd);
	ft_exit(all->errnum, NULL); //, all);
	return (1);
}

int	check_arg_export(char *str, t_all *all)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]))
	{
		ft_export_unset_error(all, str, "export");
		return (1);
	}
	while (str[i] && (str[i] == '_' || ft_isalnum(str[i])))
		i++;
	if (str[i] == '+' && str[i + 1] != '=')
	{
		ft_export_unset_error(all, str, "export");
		return (1);
	}
	return (0);
}

void	ft_env_error(t_all *all, char *str)
{
	all->errnum = 127;
	write(2, "env", 3);
	write(2, ": ", 2);
	write(2, str, ft_strlen(str));
	write(2, " : No such file or directory\n", 29);
}

int	ft_env(t_all *all, t_command *cmd)
{
	t_env	*tmp;

	if (!(all->envp))
		return (1);
	if (cmd->cmd[1])
	{
		ft_env_error(all, cmd->cmd[1]);
		return (all->errnum);
	}
	tmp = all->envp;
	while (tmp)
	{
		if (tmp->separator && !ft_strcmp(tmp->separator, "="))
		{
			ft_putstr_fd(tmp->key, 1);
			ft_putstr_fd(tmp->separator, 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putstr_fd("\n", 1);
		}
		tmp = tmp->next;
	}
	return (0);
}
