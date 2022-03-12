/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaurelio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 19:43:24 by eaurelio          #+#    #+#             */
/*   Updated: 2022/03/12 19:43:26 by eaurelio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_split_number(char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			j++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		j++;
	return (j);
}

static void	*ft_free_split(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

static int	ft_malloc_size(const char *s, const char c)
{
	int	num;

	num = 0;
	while (s[num] && s[num] != c)
		num++;
	return (num);
}

static char	**ft_subsplit(char **split, char const *s, char c, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i] && k < n)
	{
		j = 0;
		while ((char)s[i] == (char)c && (char)s[i])
			i++;
		split[k] = (char *)malloc(sizeof(char) * \
				(ft_malloc_size(s + i, c) + 1));
		if (!split[k])
			return (NULL);
		while ((char)s[i] != (char)c && (char)s[i])
			split[k][j++] = s[i++];
		split[k][j++] = '\0';
		i++;
		k++;
	}
	split[k] = NULL;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	n;

	if (!s)
		return (NULL);
	n = ft_split_number(s, c);
	split = (char **)malloc(sizeof(char *) * (n + 1));
	if (!split)
		return (NULL);
	if (!ft_subsplit(split, s, c, n))
	{
		ft_free_split(split);
		return (NULL);
	}
	return (split);
}
