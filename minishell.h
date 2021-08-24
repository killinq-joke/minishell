/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 10:13:33 by ztouzri           #+#    #+#             */
/*   Updated: 2021/08/09 18:19:49by ztouzri          ###   ########.fr       */
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
	char	operator;
	char	**path;
	char	*path_bis;
	t_env	*env;
	t_redir	*redir;
	t_link	*next;
}				t_link;

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
void	cd(t_link *cmd, t_env *env);
void	export(char **command, t_env *env);
void	unset(char **namelist, t_all *all);
void	echo(t_link *cmd);
void	pwd(void);
int		rl_replace_line(const char *str, int num);
void	echo_control_seq(t_bool c);
t_redir	*redirmaker(char **tokens);

#endif
