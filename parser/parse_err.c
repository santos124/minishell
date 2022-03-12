/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:36:29 by wadina            #+#    #+#             */
/*   Updated: 2022/03/12 18:36:30 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//точказапятой стоит некорректно
int	wrong_semicolon(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == ';')
		return (1);
	while (str[i])
	{
		if (str[i] == ';')
		{
			i++;
			while (str[i] == ' ')
				i++;
			if (str[i] == ';')
				return (1);
		}
		i++;
	}
	return (0);
}

//двойные точказапятой
int	double_semicolon(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i + 1] && str[i] == ';' && str[i + 1] == ';')
			return (1);
		i++;
	}
	return (0);
}

//некорректно пайпы
int	wrong_pipes(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '|')
		return (1);
	while (str[i])
	{
		if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		{
			i++;
			if (str[i] && str[i] == '|')
				return (0);
			if (str[i] == '>' || str[i] == '<')
				i++;
			while (str[i] && !ft_isalnum(str[i]) && str[i] != '|')
				i++;
			if (str[i] == '|')
				return (1);
		}
		i++;
	}
	return (0);
}

//проверка на спецсимволы
char	*unexpected_token(char *str)
{
	if (str[0] == '|' && str[1] == '|')
		return ("||");
	if (wrong_pipes(str))
		return ("|");
	else if (double_semicolon(str))
		return (";;");
	else if (wrong_semicolon(str))
		return (";");
	else if (bad_redirects(str))
		return (bad_redirects(str));
	else if (empty_redir(str))
		return ("newline");
	else
		return (NULL);
}

//проверка на синтаксис
int	parse_check_err(char *str, t_all *all)
{
	if (unexpected_token(str) != NULL)
	{
		printf("minishell: syntax error near unexpected token `%s\'\n", \
			unexpected_token(str));
		all->errnum = 258;
		return (1);
	}
	else if (next_err_syntax(str) != NULL)
	{
		printf("%s\n", next_err_syntax(str));
		all->errnum = 258;
		return (1);
	}
	else
		return (0);
}
