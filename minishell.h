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
# include <signal.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"

# define QUOTE 39
# define DQUOTE 34
# define SPACE 32

typedef struct s_link	t_link;

typedef enum e_bool {
	false,
	true,
}				t_bool;

typedef struct s_link
{
	char	**command;
	t_bool	operator;
	char	**env;
	int		fd_tmp;
	t_link	*next;
}				t_link;

t_bool	checkerror(char *line);
char	**commandsplit(char *line);
char	**parstoken(char *line);
t_link	*linkinit(char **cmd, char **env);
t_link	*parspipe(char **token, char **ev);
void	givegoodpath(t_link *cmd);
void	execbuiltin(t_link *cmd);
void	execcmd(t_link *cmd);
void	execdollar(t_link *cmd);

size_t	splitlen(char **split);

#endif
