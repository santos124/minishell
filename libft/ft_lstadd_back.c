#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*llst;

	if (lst != 0 && *lst != 0)
	{
		llst = *lst;
		llst = ft_lstlast(*lst);
		llst->next = new;
		return ;
	}
	*lst = new;
}
