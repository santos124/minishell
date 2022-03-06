#include "libft.h"

char	*ft_strdup(const char *s1, t_all *all)
{
	char	*dst;
	size_t	i;

	i = 0;
	dst = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!dst)
		ft_exit(12, "malloc", all);
	if (dst)
	{
		while (s1[i])
		{
			dst[i] = s1[i];
			i++;
		}
		dst[i] = '\0';
		return (dst);
	}
	else
		return (0);
}
