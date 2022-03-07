#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2, t_all *all)
{
	size_t	i;
	size_t	j;
	char	*str;

	(void)all;
	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		ft_exit(12, "malloc"); //, all);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}
