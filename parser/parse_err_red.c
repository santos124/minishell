/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_err_red.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:36:21 by wadina            #+#    #+#             */
/*   Updated: 2022/03/12 18:36:23 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*second_wrong(char *str)
{
	if (str[1] && str[0] == '>' && str[1] == '>')
		return (">>");
	else if (str[0] == '>')
		return (">");
	else if (str[1] && str[0] == '<' && str[1] == '<')
		return ("<<");
	else if (str[0] == '<')
		return ("<");
	else
		return (NULL);
}

char	*bad_redirects(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			i++;
			if (str[i] == '<' || str[i] == '>')
				i++;
			while (str[i] == ' ')
				i++;
			if (str[i] == '<' || str[i] == '>')
				return (second_wrong(&str[i]));
		}
		i++;
	}
	return (NULL);
}

int	empty_redir(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (str[i] && str[i] == ' ')
		i--;
	if (str[i] == '<' || str[i] == '>')
		return (1);
	return (0);
}
