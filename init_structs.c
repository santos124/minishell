#include "minishell.h"

void	ft_init_structs(t_all **all)
{
	(*all) = (t_all *)malloc(sizeof (t_all));
	if (!(*all))
		ft_exit(12, "malloc", NULL);
	(*all)->cmd = NULL;
	(*all)->redir = NULL;
	(*all)->envp = NULL;
	(*all)->num = 0;
	(*all)->num_cmd = 0;
	(*all)->errnum = 0;
	(*all)->fd = NULL;
}
