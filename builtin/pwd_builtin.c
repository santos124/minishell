/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:15:45 by wadina            #+#    #+#             */
/*   Updated: 2022/03/12 18:16:47 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_all *all)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		err_exit(errno, "getcwd");
	ft_putendl_fd(pwd, 1);
	free_null((void **)&pwd);
	all->errnum = 0;
	return (0);
}
