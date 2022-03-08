#include "../minishell.h"

//пайп в конце
int	last_pipe(char *line)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (line[i] && line[i] == ' ')
		i--;
	if (line[i] == '|')
		return (1);
	return (0);
}

//незакрытые одинарные кавычки
int	unclosed_quotes(char *line)
{
	int	i;
	int	quotes1;
	int	quotes2;

	i = 0;
	quotes1 = 0;
	quotes2 = 0;
	while (line[i])
	{
		if (line[i] == '\'' && quotes1 == 0)
			quotes1++;
		else if (line[i] == '\'')
			quotes1--;
		i++;
	}
	if (quotes1 || quotes2)
		return (1);
	return (0);
}

//незакрытые двойные кавычки
int	unclosed_doub_qts(char *line)
{
	int	i;
	int	quotes1;
	int	quotes2;

	i = 0;
	quotes1 = 0;
	quotes2 = 0;
	while (line[i])
	{
		if (line[i] == '\"' && quotes2 == 0)
			quotes2++;
		else if (line[i] == '\"')
			quotes2--;
		i++;
	}
	if (quotes1 || quotes2)
		return (1);
	return (0);
}

char	*next_err_syntax(char *line)
{
	if (last_pipe(line))
		return ("minishell: syntax error: unexpected end of file");
	else if (unclosed_quotes(line))
		return ("minishell: unexpected EOF while looking for matching `\'\'");
	else if (unclosed_doub_qts(line))
		return ("minishell: unexpected EOF while looking for matching `\"\'");
	else
		return (NULL);
}

//табы и '\n' заменить на пробелы
void	format_blanks(char **line)
{
	int	i;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '\t' || (*line)[i] == '\n')
			(*line)[i] = ' ';
		i++;
	}
}
