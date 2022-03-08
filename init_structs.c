#include "minishell.h"

void	init_struct(t_all **all)
{
	(*all) = (t_all *)malloc(sizeof (t_all));
	if (!(*all))
		err_exit(12, "malloc"); //, NULL);
	(*all)->cmd = NULL;
	(*all)->red = NULL;
	(*all)->envp = NULL;
	(*all)->num = 0;
	(*all)->num_cmd = 0;
	(*all)->errnum = 0;
	(*all)->fd = NULL;
}
