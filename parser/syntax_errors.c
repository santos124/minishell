#include "../minishell.h"

//некорректно пайпы
int	wrong_pipes(char *line)
{
	int		i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '|')
		return (1);
	while (line[i])
	{
		if (line[i] == '|' || line[i] == '>' || line[i] == '<')
		{
			i++;
			if (line[i] && line[i] == '|')
				return (0);
			if (line[i] == '>' || line[i] == '<')
				i++;
			while (line[i] && !ft_isalnum(line[i]) && line[i] != '|')
				i++;
			if (line[i] == '|')
				return (1);
		}
		i++;
	}
	return (0);
}

//точказапятой стоит некорректно
int	wrong_semicolon(char *line)
{
	int		i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == ';')
		return (1);
	while (line[i])
	{
		if (line[i] == ';')
		{
			i++;
			while (line[i] == ' ')
				i++;
			if (line[i] == ';')
				return (1);
		}
		i++;
	}
	return (0);
}

//двойные точказапятой
int	double_semicolon(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i + 1] && line[i] == ';' && line[i + 1] == ';')
			return (1);
		i++;
	}
	return (0);
}

//проверка на спецсимволы
char	*unexpected_token(char *line)
{
	if (line[0] == '|' && line[1] == '|')
		return ("||");
	if (wrong_pipes(line))
		return ("|");
	else if (double_semicolon(line))
		return (";;");
	else if (wrong_semicolon(line))
		return (";");
	else if (bad_redirects(line))
		return (bad_redirects(line));
	else if (empty_redir(line))
		return ("newline");
	else
		return (NULL);
}

//проверка на синтаксис
int	parse_check_err(char *line, t_all *all)
{
	if (unexpected_token(line))
	{
		printf("minishell: syntax error near unexpected token `%s\'\n", \
			unexpected_token(line));
		all->errnum = 258;
		return (1);
	}
	else if (next_err_syntax(line))
	{
		printf("%s\n", next_err_syntax(line));
		all->errnum = 258;
		return (1);
	}
	else
		return (0);
}
