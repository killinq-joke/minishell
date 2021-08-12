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
# include "libft.h"

# define QUOTE '\''
# define DQUOTE '"'
# define SPACE 32

typedef struct s_link	t_link;
typedef struct s_env	t_env;

typedef enum e_bool {
	false,
	true,
}				t_bool;

typedef struct s_env
{
	char	*name;
	char	*value;
	t_env	*next;
}				t_env;

typedef struct s_link
{
	char	**command;
	t_bool	operator;
	char	**path;
	char	*path_bis;
	t_env	*env;
	int		fd_tmp;
	t_link	*next;
}				t_link;

t_bool	checkerror(char *line);
char	**commandsplit(char *line);
char	**parstoken(char *line);
t_link	*linkinit(char **cmd);
t_link	*parspipe(char **token);
void	give_good_path(t_link *cmd, t_env *env);
void	execbuiltins(t_link *cmd, t_env *env);
void	execcmd(t_link *cmd);
void	execdollar(t_link *cmd);
t_env	*envinit(char *name, char *value);
t_env	*envmaker(char **env);
void	printenv(t_env *env);
void	givepath(t_env *path, t_link *cmd);
size_t	splitlen(char **split);

#endif
