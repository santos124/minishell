#include "libft.h"

void	*ft_memset(void *dest, int c, size_t len)
{
	size_t			i;
	unsigned char	*b;

	i = 0;
	b = dest;
	while (i < len)
	{
		*(b + i) = c;
		i++;
	}
	return (b);
}
