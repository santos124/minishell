#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst)
	{
		if (del && lst->content != 0)
			del(lst->content);
		free(lst);
		lst = 0;
	}
}
