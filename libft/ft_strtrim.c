#include "libft.h"

static int	ft_charset(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if ((unsigned char)set[i] == (unsigned char)c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	if (!s1)
		return (NULL);
	j = ft_strlen(s1);
	if (!set)
		return ((char *)s1);
	while (s1[i] && ft_charset(s1[i], set))
		i++;
	while (j > i && ft_charset(s1[j - 1], set))
		j--;
	str = (char *)malloc(sizeof(*s1) * (j - i + 1));
	if (!str)
		return (NULL);
	while (j > i)
		str[k++] = (char)s1[i++];
	str[k] = '\0';
	return (str);
}
