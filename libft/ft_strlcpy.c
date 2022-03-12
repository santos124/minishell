/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaurelio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 19:44:11 by eaurelio          #+#    #+#             */
/*   Updated: 2022/03/12 19:44:12 by eaurelio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!src)
		return (0);
	if (size > 0)
	{
		while (*(src + i) && i < size - 1)
		{
			*(char *)(dst + i) = *(char *)(src + i);
			i++;
		}
		*(char *)(dst + i) = '\0';
	}
	while (*(src + i))
		i++;
	return (i);
}
