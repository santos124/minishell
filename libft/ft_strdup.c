#include "libft.h"

char	*ft_strdup (const char *s1)
{
	char	*s2;

	s2 = ft_calloc(ft_strlen(s1) + 1, sizeof(char));
	if (NULL == s2)
		ft_exit(12, "malloc");
	ft_memmove(s2, s1, ft_strlen(s1));
	return (s2);
}