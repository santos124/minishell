/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_err_sec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:37:49 by wadina            #+#    #+#             */
/*   Updated: 2022/03/12 18:37:51 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//пайп в конце
int	last_pipe(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (str[i] && str[i] == ' ')
		i--;
	if (str[i] == '|')
		return (1);
	return (0);
}

//незакрытые одинарные кавычки
int	unclosed_quotes(char *str)
{
	int	quotes1;
	int	quotes2;
	int	i;

	quotes1 = 0;
	quotes2 = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && quotes1 == 0)
			quotes1++;
		else if (str[i] == '\'')
			quotes1--;
		i++;
	}
	if (quotes1 || quotes2)
		return (1);
	return (0);
}

//незакрытые двойные кавычки
int	unclosed_doub_qts(char *str)
{
	int	quotes1;
	int	quotes2;
	int	i;

	quotes1 = 0;
	quotes2 = 0;
	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == '\"' && quotes2 == 0)
			quotes2++;
		else if (str[i] == '\"')
			quotes2--;
		i++;
	}
	if (quotes1 || quotes2)
		return (1);
	return (0);
}

char	*next_err_syntax(char *str)
{
	if (last_pipe(str))
		return ("minishell: syntax error: unexpected end of file");
	else if (unclosed_quotes(str))
		return ("minishell: unexpected EOF while need `\'\'");
	else if (unclosed_doub_qts(str))
		return ("minishell: unexpected EOF while need `\"\'");
	else
		return (NULL);
}

//табы и '\n' заменить на пробелы
void	format_blanks(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\n' || (*str)[i] == '\t')
			(*str)[i] = ' ';
		i++;
	}
}
