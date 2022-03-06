#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)src)[i] == (unsigned char) c)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			return ((void *)(dst + i + 1));
		}
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (0);
}
