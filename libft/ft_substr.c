/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaurelio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 19:46:25 by eaurelio          #+#    #+#             */
/*   Updated: 2022/03/12 19:46:27 by eaurelio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*s1;
	size_t	k;

	i = (size_t) start;
	j = 0;
	if (!s)
		return (NULL);
	k = ft_strlen(s);
	if (len > k + 1)
		s1 = (char *)malloc(sizeof(*s) * (k + 1));
	if (len <= k + 1)
		s1 = (char *)malloc(sizeof(*s) * (len + 1));
	if (!s1)
		return (NULL);
	if (i > ft_strlen(s))
	{
		s1[j] = '\0';
		return (s1);
	}
	while (s[i] && j < len)
		s1[j++] = (char)s[i++];
	s1[j] = '\0';
	return (s1);
}
