/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 10:13:33 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/12 16:57:19 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <signal.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <termios.h>
# include <dirent.h>
# include "libft.h"

# define QUOTE '\''
# define DQUOTE '"'
# define SPACE 32

typedef struct s_link	t_link;
typedef struct s_env	t_env;
typedef struct s_all	t_all;
typedef struct s_redir	t_redir;

typedef enum e_bool {
	false,
	true,
}				t_bool;

typedef struct g_signal {
	pid_t	childpid;
	char	**path;
	char	**env;
	int		fd[2];
	int		i;
	int		co;
	char	*command;
	char	*tmp;
	char	tmpp;
	int		out;
	int		fdd;
	int		taille;
	int		kill;
	int		file;
	int		filee;
	int		u;
	t_link	*actuel;
	t_redir	*current;
	t_bool	errorleft;
	t_bool	redir;
	t_bool	heredoc;
	t_bool	heredocuse;
	t_bool	interrupt;
	t_all	*all;
}				t_signal;

typedef struct s_all
{
	t_env	*headenv;
	t_link	*headcmd;
	int		exit_status;	
}				t_all;

typedef struct s_redir
{
	char	*redir;
	char	*arg;
	t_redir	*next;
}				t_redir;

typedef struct s_env
{
	char	*name;
	char	*value;
	t_env	*next;
}				t_env;

typedef struct s_link
{
	char	**command;
	char	**path;
	char	*path_bis;
	t_redir	*redir;
	t_link	*next;
}				t_link;

typedef struct s_pars
{
	int		i;
	int		j;
	int		k;
	int		count;
	int		nbquote;
	char	*res;
	char	*tmp;
	char	*tmp1;
	char	*name;
	t_bool	indquote;
}				t_pars;

t_bool	checkerror(char *line);
char	**commandsplit(char *line);
char	**parstoken(char *line);
t_link	*linkinit(char **cmd);
t_link	*parspipe(char **token);
void	give_good_path(t_all *all);
void	execbuiltins(t_all *all);
void	execcmd(t_link *cmd);
void	execdollar(t_link *cmd);
t_env	*envinit(char *name, char *value);
t_env	*envmaker(char **env);
void	printenv(t_env *env);
void	givepath(t_env *env, t_link *cmd);
size_t	splitlen(char **split);
char	*getname(char *envstr);
size_t	linklen(t_link *head);
size_t	envlen(t_env *head);
void	minishell(t_all *all, t_link *cmd);
char	*ft_getenv(const char *name, t_env *env);
void	exportt(char **command, t_env *env);
void	cd(t_link *cmd, t_env *env, t_all *all);
void	export(char **command, t_env *env);
void	export2(char **command, t_env *env, char *tmp1, t_env *current);
void	unset(char **namelist, t_all *all);
void	echo(t_link *cmd);
void	pwd(void);
int		rl_replace_line(const char *str, int num);
void	echo_control_seq(t_bool c);
void	redirmaker(t_link *cmd);
void	printredir(t_redir *redir);
void	printsplit(char **split);
char	*parsenv(t_all *all, char *line, t_env *env);
int		counttoken(char *line);
void	cleancommand(t_link *cmd);
char	**joinstr(char **split, char *str);
char	**redirremover(char **tokens);
char	**envtab(t_env	*env);
void	freeenv(t_env *node);
void	freelink(t_link *cmd);
void	freetokens(char **tokens);
void	redirection_builtins_pipe(void);
void	file_error_and_close_builtins_pipe(int nb);
void	exec_builtins_pipe(t_all *all);
void	exec_slash_command(t_all *all);
void	file_error_and_close_slash_command_pipe(t_all *all);
void	redirection_slash_command_pipe(void);
void	exec_command_pipe(t_all *all);
void	error_path_exec_command_pipe(t_all *all);
int		heredoc_non_pipe_command(t_link *actuel, int tmpp);
void	redirection_builtins_non_pipe(void);
void	exec_builtins_non_pipe(t_all *all);
void	exec_builtins_non_pipe_2(t_all *all);
void	redirection_slash_command_non_pipe(void);
void	exec_slash_command_non_pipe(t_all *all);
void	error_path_slash_command(t_all *all);
void	error_path_exec_command(t_all *all);
void	redirection_exec_command_non_pipe(void);
void	exec_command_non_pipe(t_all *all);
void	all_pipe_execution(t_all *all);
void	all_exec_command_pipe(t_all *all);
void	all_slash_command_pipe(t_all *all);
void	all_builtin_execution_pipe(t_all *all);
void	all_non_pipe_execution(t_all *all);
void	all_exec_command_non_pipe(t_all *all);
void	all_slash_command_non_pipe(t_all *all);
void	all_builtin_execution_non_pipe(t_all *all);
void	exec_builtins_non_pipe_3(t_all *all);
void	exec_command_pipe3(void);
void	redirection_exec_command_pipe3(void);
void	redirection_exec_command_pipe2(void);
void	exec_command_non_pipe2(t_all *all);
char	*joinandfree(char *line, char c);
void	parsenv1(t_all *all, char *line, t_env *env, t_pars *p);
void	parsenv12(t_env *env, t_pars *p);
void	parsenv11(t_all *all, t_pars *p);
void	minishell2(char *tmp, char *line, t_all *all);
void	complete_minishell(t_all *all);
char	*getvalue(const char *name);
t_bool	envisin(const char *name, t_env *env);
t_bool	isplusequal(char *envstr);
void	export3(char *command, char *name);
int		heredoc_non_pipe_command3(int tmpp, t_redir *current, char *line);
int		heredoc_non_pipe_command2(int tmpp);
int		is_a_num(char *c);

#endif
