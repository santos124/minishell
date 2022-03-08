#include "libft.h"

static int	ft_abs_number(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static void	ft_strrev(char *s)
{
	size_t	i;
	size_t	n;
	char	c;

	i = 0;
	n = ft_strlen(s);
	while (i < n / 2)
	{
		c = s[i];
		s[i] = s[n - i - 1];
		s[n - i - 1] = c;
		i++;
	}
}

static int	ft_size_number(int n)
{
	int		i;

	i = 1;
	while (n > 9 || n < -9)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		sign;
	size_t	i;

	i = 0;
	sign = 0;
	if (n < 0)
		sign = 1;
	s = (char *)malloc((ft_size_number(n) + sign + 1) * sizeof(char));
	if (!s)
		return (NULL);
	if (n == 0)
		s[i++] = '0';
	while (n != 0)
	{
		s[i++] = '0' + ft_abs_number(n % 10);
		n = (n / 10);
	}
	if (sign == 1)
		s[i++] = '-';
	s[i] = '\0';
	ft_strrev(s);
	return (s);
}
