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
