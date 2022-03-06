#include "libft.h"

int	ft_atoi(const char *str)
{
	int		sign;
	size_t	res;
	int		i;

	sign = 1;
	res = 0;
	i = 0;
	while ((str[i] == '\t' || str[i] == '\n' || str[i] == '\r' || str[i] == '\v'\
	|| str[i] == ' ' || str[i] == '\f') && (str[i] != '\0'))
		i++;
	if (str[i] == '-')
		sign = -1;
	if ((str[i] == '+') || (str[i] == '-'))
		i++;
	while ((str[i] >= '0' && str[i] <= '9') && (str[i] != '\0'))
	{
		res = (str[i] - '0') + res * 10;
		if (res > 2147483648 && sign == -1)
			return (0);
		if (res > 2147483647 && sign == 1)
			return (-1);
		i++;
	}
	return ((int)res * sign);
}
