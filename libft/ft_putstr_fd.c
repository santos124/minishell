#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return ;
	else
	{
		while (s[i])
		{
			write(fd, &s[i], 1);
			i++;
		}
	}
}
