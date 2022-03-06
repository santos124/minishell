#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*ps1;
	unsigned char	*ps2;

	i = 0;
	ps1 = (unsigned char *)s1;
	ps2 = (unsigned char *)s2;
	while ((i < n) && (ps1[i] == ps2[i]))
		i++;
	if (i == n)
		return (0);
	else
		return (ps1[i] - ps2[i]);
}
