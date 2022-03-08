#include "../minishell.h"

void	env_after_cd(t_all **all)
{
	t_env	*tmp;
	t_env	*tmp1;

	tmp = (*all)->envp;
	tmp1 = (*all)->envp;
	while (tmp && ft_strcmp(tmp->key, "PWD"))
		tmp = tmp->next;
	while (tmp1 && ft_strcmp(tmp1->key, "OLDPWD"))
		tmp1 = tmp1->next;
	if (tmp && tmp1)
	{
		free(tmp1->val);
		tmp1->val = ft_strdup(tmp->val); //, *all);
		free(tmp->val);
		tmp->val = getcwd(NULL, 0);
		if (!tmp->val)
			err_exit(errno, "getcwd"); //, *all);
	}
}

char	*get_cd(t_cmd *cmd, t_env *envp)
{
	char	*cd;
	char	*pwd;

	cd = NULL;
	if (cmd->cmd[1][0] != '~')
	{
		cd = getcwd(NULL, 0);
		if (!cd)
			err_exit(errno, "getcwd"); //, all);
		pwd = ft_strjoin(cd, "/");
		free(cd);
		cd = ft_strjoin(pwd, cmd->cmd[1]);
		free(pwd);
		return (cd);
	}
	while (envp && ft_strcmp(envp->key, "HOME"))
		envp = envp->next;
	if (envp)
	{
		pwd = ft_substr(cmd->cmd[1], 1, ft_strlen(cmd->cmd[1]) - 1);
		cd = ft_strjoin(envp->val, pwd);
		free(pwd);
	}
	return (cd);
}

static void	cd_error(t_all *all, char *str, int flag)
{
	all->errnum = 1;
	write(2, "cd", 2);
	write(2, ": ", 2);
	write(2, str, ft_strlen(str));
	if (flag == 1)
		write(2, " : No such file or directory\n", 29);
	if (flag == 2)
		write(2, " : Not a directory\n", 19);
}

int	ft_cd(t_all *all, t_cmd *cmd)
{
	char	*cd;

	cd = NULL;
	if (!cmd->cmd[1])
		cmd->cmd[1] = ft_strdup("~"); //, all);
	if (cmd->cmd[1][0] == '/' || cmd->cmd[1][0] == '.')
		cd = ft_strdup(cmd->cmd[1]); //, all);
	else
		cd = get_cd(cmd, all->envp);
	if (!cd)
	{
		write(2, "cd: HOME not set\n", 17);
		return (1);
	}
	if (access(cd, F_OK) == 0 && all->num == 1)
	{
		if (chdir(cd) != 0)
			cd_error(all, cmd->cmd[1], 2);
		else
			env_after_cd(&all);
	}
	else
		cd_error(all, cmd->cmd[1], 1);
	free(cd);
	return (all->errnum);
}
