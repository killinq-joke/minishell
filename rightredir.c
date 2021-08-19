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

void	right(char **command)
{
	int	file;

	file = open("z.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
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

void	left(char **command)
{
	int	file;

	file = open("z.txt", O_RDONLY);
	if (file < 3)
	{
		ft_puterr("error\n");
		return ;
	}
	if (!fork())
	{
		dup2(file, STDIN_FILENO);
		close(file);
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
	char	*text;
	char	*line;
	char	*tmp;
	int		fd[2];	

	(void)command;
	pipe(fd);
	if (!fork())
	{
		// dup2(`k);
		line = readline("heredoc> ");
		while (ft_strcmp(line, delim))
		{
			tmp = line;
			line = readline("heredoc> ");
			if (!ft_strcmp(line, delim))
				break ;
			text = ft_strjoin(tmp, line);
			text = ft_joinchar(tmp, '\n');
			free(tmp);
		}
		if (!text)
			text = ft_strdup("");
		printf("%s\n", text);
	}
	if (!fork())
	{
		if (execve(command[0], command, NULL) == -1)
		{
			printf("error %d\n", errno);
			return ;
		}
	}
}

int	main(int ac, char **av, char **ev)
{
	(void)ac;
	(void)av;
	(void)ev;
	leftleft((char *[]){"/bin/cat", "-e", "salut", NULL}, "EOF");
	// right((char *[]){"/bin/ls", NULL});
	return (0);
}
