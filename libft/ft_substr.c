#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len, t_all *all)
{
	size_t	i;
	size_t	j;
	char	*str;

	(void)all;
	if (!s)
		return (0);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	str = (char *)malloc(sizeof(*s) * (len + 1));
	if (!str)
		ft_exit(12, "malloc"); //, all);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}
