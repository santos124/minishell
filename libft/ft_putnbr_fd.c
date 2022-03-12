/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaurelio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 19:42:13 by eaurelio          #+#    #+#             */
/*   Updated: 2022/03/12 19:42:14 by eaurelio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_abs_number(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	str[15];
	int		i;
	int		minus;

	ft_bzero(str, 15);
	i = 0;
	minus = 0;
	if (n < 0)
		minus = 1;
	if (n == 0)
		str[i++] = '0';
	while (n != 0)
	{
		str[i++] = '0' + ft_abs_number(n % 10);
		n = (n / 10);
	}
	i--;
	if (minus != 0)
		write(fd, "-", 1);
	while (i >= 0)
		write(fd, &str[i--], 1);
}
