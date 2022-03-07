#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env //переменные среды список
{
	char			*key; //ключ
	char			*sep; //*separator; //разделитель
	char			*val;//*value; //значение
	struct s_env	*next; //следующая в первоначальном порядке
	struct s_env	*a_z_next; //*alpha_next; //следующая в упорядоченном
			// алфавитном порядке
}	t_env;

typedef struct s_redirect//s_redir //редирект список
{
	char				*name; // команда которая учавствует обьектом редиректа или хирдок
	char				*limiter; //при заднем редиректе двойном  << команда
	// записывается сюда
	// ??????????
	int					cmd; // порядковый номер команды для редиректа
	int					last;//target; // крайний редирект 1/0
	int					doub; //two; //двойной редирект >> 1/0
	int					in; //входной редирект 1/0
	struct s_redirect	*next;//s_redir	*next; //следующий редирект после этого
	struct s_redirect	*all_next;//s_redir	*all_next; //следующий редирект в
	// общем
	// списке
}	t_red; //t_redir;

typedef struct s_cmd //команда список
{
	char			**cmd; //команда в терминал
	t_red			*in;   //редирект < /УКАЗАТЕЛЬ
	t_red			*out;  //редирект > /УКАЗАТЕЛЬ
	int				id_cmd;//built; //номер реализованной команды 1-7
	struct s_cmd	*next; // указатель на следующий элемент команды
}	t_cmd; //t_cmd;

typedef struct s_all
{
	t_red			*red;//ir			*redir; //редирект
	int				**fd; //?????????
	t_env			*envp; //указатель на переменную окружения
	t_env			*a_envp;//*envp_alpha; //переменная окружения самая первая
	char			**env;
	t_cmd			*cmd;//t_cmd		*cmd; //команда
	int				num; //число команд ???????????
	int				num_cmd; //число команд  ???????????
	int				errnum; //убрать потому что не используем больше
}	t_all;

// неудивляться если не будет компилиться из-за t_all
//char	**ft_split(char const *str, char c, t_all *all); // засунуть в libft
//char	*ft_strdup(const char *s1); //, t_all *all); //
//char	*ft_strjoin(char const *s1, char const *s2, t_all *all); //
//char	*ft_substr(char const *s, unsigned int start, size_t len)
; //
//char	*ft_itoa(int n, t_all *all); //

void	ft_print_all(t_all *all);

/*./parser*/
void	rl_replace_line(const char *str, int num);
int		rl_clear_history(void);
void	go_readline(char **line, t_all *all);

char	*wrong_redirects(char *line);
int		empty_redirect(char *line);
char	*other_syntax_cases(char *line);
void	tabs_to_spaces(char **line);

int		parser(t_all *all, char *line);
int		check_syntax(char *line, t_all *all);
char	*single_quotes(char *line, int *i, t_all *all);
char	*double_quotes(char *line, int *i, t_all *all);

char	*parse_redirects(char *line, int *i, t_cmd *cmd, t_all *all);
t_red	*new_redir(char *line, int *i, t_all *all);
char	*save_redir_name(char *line, int *i);
void	all_redir_list(t_red *new, t_all *all);

void	parse_env(char **envp, t_all *all);
t_env	*env_create_new(char *key, char *sep, char *value);
void	env_add_new(char *env_str, t_env **start);
char	*env_replace(char *line, int *i, t_env *envp);
char	*exit_code_replace(char *line, t_all *all, int *i);
void	sort_env(t_all *all);

/*signals*/
void	sig_handler_child(int sig_num);
void	sig_handler_parent(int sig_num);
void	heredoc_sig_int(int sig);

/*utils*/
int		ft_count_cmd(t_cmd *cmd);
int		ft_count_envp(t_env *envp);
void	ft_env_list_to_array(t_env *envp, t_all *all);
void	ft_make_array(t_env *envp, char **env, int len);
void	ft_print_error(int errnum, char *str, char *cmd_name);

/*check_open.c*/
int		check_open(t_all *all);

/*child.c*/
void	child_process(int i, t_all *all);
void	execute(char **cmd, char **env, t_all *all);
char	*find_path(char *cmd, char **envp);
int		ft_check_path(t_all *all, char *cmd);
int		check_x(t_all *all, char *path, char *cmd);

/*redirects.c*/
int		dup_cmd(t_cmd *cmd); //, t_all *all);
void	redup_cmd(int fd); //, t_all *all);

/*pipe.c*/
void	ft_pipe(t_all *all);

/*pipex.c*/
void	pipex(t_all *all);
void	ft_dup2(int i, int *file, t_cmd *cmd, t_all *all);

/*./built_in*/
int		ft_cd(t_all *all, t_cmd *cmd);
int		ft_pwd(t_all *all);
int		ft_env(t_all *all, t_cmd *cmd);
int		ft_echo(t_all *all, t_cmd *cmd);
int		ft_unset(t_cmd *cmd, t_all *all);
int		ft_export(t_all *all, t_cmd *cmd);
int		ft_add_new(char *str, t_all *all);
// int		ft_export_join(char *new, t_env *envp, t_all *all);
void	ft_export_unset_error(t_all *all, char *str, char *namecmd);
int		check_arg_export(char *str, t_all *all);
void	ft_cd_error(t_all *all, char *str, int flag);
int		ft_exit_cmd(t_all *all, t_cmd *cmd);
int		check_exit(t_all *all);
int		ft_exit(int errnum, char *msg); //, t_all *all);
void	free_structs(t_all *all);
int		ft_last_err(t_all *all);

void	ft_shlvl_check(t_all *all);
void	ft_init_structs(t_all **all);
int		run_built(t_cmd *cmd, t_all *all);
void	heredoc(char *name, char *limiter, t_all *all);

#endif
