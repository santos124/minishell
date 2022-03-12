/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaurelio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 19:41:00 by eaurelio          #+#    #+#             */
/*   Updated: 2022/03/12 19:41:02 by eaurelio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*sn1;
	unsigned char	*sn2;

	i = 0;
	sn1 = (unsigned char *)s1;
	sn2 = (unsigned char *)s2;
	while (i < n)
	{
		if (*(sn1 + i) != *(sn2 + i))
			return (*(sn1 + i) - *(sn2 + i));
		i++;
	}
	return (0);
}
