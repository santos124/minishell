#include "libft.h"

static int	ft_nbrlen(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n, t_all *all)
{
	int		i;
	int		len_n;
	char	*str;

	(void)all;
	i = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648")); //, all));
	len_n = ft_nbrlen(n);
	str = (char *)malloc(sizeof(char) * (len_n + 1));
	if (!str)
		ft_exit(12, "malloc"); //, all);
	str[len_n] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
		i++;
	}
	while (i < len_n--)
	{
		str[len_n] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
