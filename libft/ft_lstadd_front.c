#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *list)
{
	list->next = *lst;
	*lst = list;
}
