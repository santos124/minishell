/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 19:12:11 by wadina            #+#    #+#             */
/*   Updated: 2022/03/12 19:33:51 by eaurelio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_env
{
	char			*key;
	char			*sep;
	char			*val;
	struct s_env	*next;
	struct s_env	*a_z_next;
}	t_env;

typedef struct s_redirect
{
	char				*name;
	char				*limiter;
	int					cmd;
	int					last;
	int					doub;
	int					in;
	struct s_redirect	*next;
	struct s_redirect	*all_next;
}	t_red;

typedef struct s_cmd
{
	char			**cmd;
	t_red			*in;
	t_red			*out;
	int				id_cmd;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_all
{
	t_red			*red;
	int				**fd;
	t_env			*envp;
	t_env			*a_envp;
	char			**env;
	t_cmd			*cmd;
	int				num;
	int				num_cmd;
	int				errnum;
}	t_all;

void	free_null(void **ptr);
/*./parser*/
void	rl_replace_line(const char *str, int num);
int		rl_clear_history(void);
void	get_line(char **line, t_all *all);
char	*bad_redirects(char *line);
int		empty_redir(char *line);
char	*next_err_syntax(char *line);
void	format_blanks(char **line);
int		parser(t_all *all, char *line);
int		parse_check_err(char *line, t_all *all);
char	*single_qts(char *line, int *i);
char	*doub_qts(char *line, int *i, t_all *all);
char	*parsing_reds(char *line, int *i, t_cmd *cmd, t_all *all);
t_red	*new_red(char *line, int *i, t_all *all);
char	*name_red(char *line, int *i);
void	list_reds(t_red *new, t_all *all);
void	parse_env(char **envp, t_all *all);
void	add_env(char *env_str, t_env **start);
char	*replace_var(char *line, int *i, t_env *envp);
char	*get_last_exit_code(char *line, t_all *all, int *i);
void	sort_env(t_all *all);
/*signals*/
void	handler_child(int sig_num);
void	handler_parent(int sig_num);
void	handler_heredoc(int sig);
/*utils*/
int		count_cmd(t_cmd *cmd);
int		count_env(t_env *envp);
void	env_to_arr(t_env *envp, t_all *all);
void	new_arr(t_env *envp, char **env, int len);
void	print_error(int errnum, char *str, char *cmd_name);
/*check_open.c*/
int		open_file(t_all *all);
/*child.c*/
void	run_child(int i, t_all *all);
int		valid_path(t_all *all, char *cmd);
/*redirects.c*/
int		dup_cmd(t_cmd *cmd);
void	redup_cmd(int fd);
/*pipe.c*/
void	ft_close(t_all *all, int *fd, int num);
void	ft_pipe(t_all *all);
/*pipex.c*/
void	pipex(t_all *all);
void	ft_dup2(int *fd, t_all *all, t_cmd *cmd, int i);
/*./builtin*/
int		ft_cd(t_all *all, t_cmd *cmd);
int		ft_pwd(t_all *all);
int		ft_env(t_all *all, t_cmd *cmd);
int		ft_echo(t_cmd *cmd);
int		ft_unset(t_cmd *cmd, t_all *all);
int		ft_export(t_all *all, t_cmd *cmd);
void	env_print_err(t_all *all, char *str, char *namecmd);
int		check_env(char *str, t_all *all);
int		ft_exit(t_all *all, t_cmd *cmd);
int		err_exit(int errnum, char *msg);
void	free_struct(t_all *all);
void	shlvl_check(t_all *all);
int		run_builtin(t_cmd *cmd, t_all *all);
void	heredoc_open(char *name, char *limiter, t_all *all);

#endif
