/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:35:54 by wadina            #+#    #+#             */
/*   Updated: 2022/03/12 18:35:55 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_quotes(char *str, int start, int *i)
{
	int	len;
	int	j;

	len = ft_strlen(str);
	j = 0;
	while (start + j < *i - 1)
	{
		str[start + j] = str[start + j + 1];
		j++;
	}
	while (start + j < len - 2)
	{
		str[start + j] = str[start + j + 2];
		j++;
	}
	while (start + j < len)
	{
		str[start + j] = 0;
		j++;
	}
}

//del all
char	*single_qts(char *str, int *i)
{
	int		start;

	start = *i;
	(*i)++;
	while (str[*i] && str[*i + 1] && str[*i] != '\'')
	{
		if (str[*i] == ' ')
			str[*i] = '\a';
		(*i)++;
	}
	remove_quotes(str, start, i);
	(*i) -= 2;
	return (str);
}

char	*doub_qts(char *str, int *i, t_all *all)
{
	int		start;

	start = *i;
	(*i)++;
	while (str[*i] && str[*i + 1] && str[*i] != '\"')
	{
		if (str[*i] == '$' && (str[*i + 1] == '_' || ft_isalpha(str[*i + 1])))
		{
			str = replace_var(str, i, all->envp);
			(*i)--;
		}
		if (str[*i] == ' ')
			str[*i] = '\a';
		(*i)++;
	}
	remove_quotes(str, start, i);
	(*i) -= 2;
	return (str);
}
