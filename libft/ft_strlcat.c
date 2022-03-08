#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dstlen;
	size_t	srclen;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	i = dstlen;
	j = 0;
	if (dstsize > dstlen + 1 && dstsize > 0)
	{
		while (*(src + j) && dstlen + j < dstsize - 1)
		{
			*(dst + i) = *(src + j);
			i++;
			j++;
		}
		*(dst + i) = '\0';
		return (dstlen + srclen);
	}
	if (dstsize == dstlen + 1)
		return (dstlen + srclen);
	return (srclen + dstsize);
}
