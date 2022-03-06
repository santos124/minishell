#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*lstnew;

	lstnew = (t_list *)malloc(sizeof (*lstnew));
	if (!lstnew)
		return (0);
	lstnew->content = content;
	lstnew->next = 0;
	return (lstnew);
}
