/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rightredir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 09:31:05 by ztouzri           #+#    #+#             */
/*   Updated: 2021/08/18 15:20:39by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	right(t_link *cmd)
{
	int	file;

	file = open(cmd->redir->arg, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (file < 3)
		return ;
	if (!fork())
	{
		dup2(file, STDOUT_FILENO);
		if (execve(command[0], command, NULL) == -1)
		{
			printf("error %d\n", errno);
			close(file);
			return ;
		}
		close(file);
	}
}

// void	right(char **command)
// {
// 	int	file;

// 	file = open("z.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
// 	if (file < 3)
// 		return ;
// 	if (!fork())
// 	{
// 		dup2(file, STDOUT_FILENO);
// 		if (execve(command[0], command, NULL) == -1)
// 		{
// 			printf("error %d\n", errno);
// 			close(file);
// 			return ;
// 		}
// 		close(file);
// 	}
// }

void	rightright(char **command)
{
	int	file;

	file = open("z.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
	if (file < 3)
		return ;
	if (!fork())
	{
		dup2(file, STDOUT_FILENO);
		if (execve(command[0], command, NULL) == -1)
		{
			printf("error %d\n", errno);
			close(file);
			return ;
		}
		close(file);
	}
}

void	left(int filed, char **command)
{
	if (filed < 3)
	{
		ft_puterr("error\n");
		return ;
	}
	if (!fork())
	{
		dup2(filed, STDIN_FILENO);
		close(filed);
		if (execve(command[0], command, NULL) == -1)
		{
			ft_puterr("error\n");
			return ;
		}
	}
}

char	**splitjoin(char **split, char *str)
{
	int		i;
	char	**join;

	join = ft_calloc(splitlen(split) + 1, sizeof (char *));
	i = 0;
	while (split[i])
	{
		join[i] = split[i];
		i++;
	}
	split[i++] = str;
	split[i] = NULL;
	return (join);
}

void	leftleft(char **command, char *delim)
{
	char	*line;
	char	*tmp;
	int		file;

	file = open("/tmp/hd", O_CREAT | O_TRUNC | O_WRONLY, 0600);
	line = readline("heredoc> ");
	while (ft_strcmp(line, delim))
	{
		write(file, line, ft_strlen(line));
		write(file, "\n", 1);
		tmp = line;
		line = readline("heredoc> ");
		free(tmp);
	}
	free(line);
	if (!fork())
	{
		file = open("/tmp/hd", O_RDONLY);
		unlink("/tmp/hd");
		dup2(file, STDIN_FILENO);
		close(file);
		if (execve(command[0], command, NULL) == -1)
			ft_puterr("error");
	}
}

int	main(int ac, char **av, char **ev)
{
	(void)ac;
	(void)av;
	(void)ev;
	leftleft((char *[]){"/bin/cat", "-e", NULL}, "EOF");
	// right((char *[]){"/bin/ls", NULL});
	return (0);
}
