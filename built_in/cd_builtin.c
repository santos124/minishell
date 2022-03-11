#include "../minishell.h"

static void	cd_error(t_all *all, char *str, int flag)
{
	all->errnum = 1;
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(str, 2);
	if (flag == 1)
		ft_putstr_fd(" : No such file or directory\n", 2);
	if (flag == 2)
		ft_putstr_fd(" : Not a directory\n", 2);
}

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
		free_null((void**)&tmp1->val);
		tmp1->val = ft_strdup(tmp->val);
		free_null((void**)&tmp->val);
		tmp->val = getcwd(NULL, 0);
		if (!tmp->val)
			err_exit(errno, "getcwd");
	}
}

char	*get_cd(t_cmd *cmd, t_env *env)
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
		free_null((void**)&cd);
		cd = ft_strjoin(pwd, cmd->cmd[1]);
		free_null((void**)&pwd);
		return (cd);
	}
	while (env && ft_strcmp(env->key, "HOME"))
		env = env->next;
	if (env)
	{
		pwd = ft_substr(cmd->cmd[1], 1, ft_strlen(cmd->cmd[1]) - 1);
		cd = ft_strjoin(env->val, pwd);
		free_null((void**)&pwd);
	}
	return (cd);
}

int	ft_cd(t_all *all, t_cmd *cmd)
{
	char	*cd;

	cd = NULL;
	if (!cmd->cmd[1])
		cmd->cmd[1] = ft_strdup("~");
	if (cmd->cmd[1][0] == '/' || cmd->cmd[1][0] == '.')
		cd = ft_strdup(cmd->cmd[1]);
	else
		cd = get_cd(cmd, all->envp);
	if (!cd)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
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
	free_null((void**)&cd);
	return (all->errnum);
}
