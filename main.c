/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 18:26:20 by ztouzri           #+#    #+#             */
/*   Updated: 2021/08/24 14:11:37by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_signal	g_signal;

int	counttoken(char *line)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	if (line[i] && line[i] != SPACE && line[i] != DQUOTE && line[i] != QUOTE)
		count++;
	while (line[i])
	{
		if (line[i] == SPACE)
		{
			while (line[i] == SPACE)
				i++;
			if (line[i])
				count++;
		}
		if (line[i] == DQUOTE)
		{
			i++;
			while (line[i] && line[i] != DQUOTE)
				i++;
			if (line[i] != DQUOTE)
			{
				ft_puterr("error: unclosed dquotes not supported\n");
				return (-1);
			}
			count++;
		}
		if (line[i] == QUOTE)
		{
			i++;
			while (line[i] && line[i] != QUOTE)
				i++;
			if (line[i] != QUOTE)
			{
				ft_puterr("error: unclosed quotes not supported\n");
				return (-1);
			}
			count++;
		}
		if (!line[i])
			break ;
		i++;
	}
	return (count);
}

char	*parsenv(t_all *all, char *line, t_env *env)
{
	int		i;
	int		j;
	char	*res;
	char	*tmp;
	char	*tmp1;
	char	*name;
	t_bool	indquote;

	res = ft_calloc(1, sizeof (char));
	i = 0;
	indquote = false;
	while (line[i])
	{
		if (line[i] && line[i] == QUOTE)
		{
			tmp = res;
			res = ft_joinchar(tmp, line[i]);
			free(tmp);
			i++;
			while (line[i] && line[i] != QUOTE)
			{
				tmp = res;
				res = ft_joinchar(tmp, line[i]);
				free(tmp);
				i++;
			}
			if (line[i] && line[i] == QUOTE)
			{
				tmp = res;
				res = ft_joinchar(tmp, line[i]);
				free(tmp);
			}
		}
		else if (line[i] && line[i] == '$')
		{
			if (line[i] && line[i + 1] != SPACE)
			{
				j = 0;
				while (line[i + j + 1] && line[i + j + 1] != SPACE
					&& line[i + j + 1] != QUOTE && line[i + j + 1] != DQUOTE)
					j++;
				name = ft_substr(&line[1], i, j);
				if (!ft_strcmp(name, "?"))
				{
					tmp = res;
					tmp1 = ft_itoa(all->exit_status);
					res = ft_strjoin(tmp, tmp1);
					free(tmp1);
					free(tmp);
				}
				else
				{
					tmp = res;
					res = ft_strjoin(tmp, ft_getenv(name, env));
					free(tmp);
				}
				i += j;
			}
		}
		else
		{
			if (line[i] == DQUOTE)
				indquote = !indquote;
			if ((!ft_strncmp(">>", &line[i], 2) || !ft_strncmp("<<", &line[i], 2)) && !indquote)
			{
				tmp = res;
				res = ft_joinchar(tmp, ' ');
				free(tmp);
				tmp = res;
				res = ft_joinchar(tmp, line[i++]);
				free(tmp);
				tmp = res;
				res = ft_joinchar(tmp, line[i]);
				free(tmp);
				tmp = res;
				res = ft_joinchar(tmp, ' ');
				free(tmp);
			}
			else if (ft_isin("><|", line[i]) && !indquote)
			{
				tmp = res;
				res = ft_joinchar(tmp, ' ');
				free(tmp);
				tmp = res;
				res = ft_joinchar(tmp, line[i]);
				free(tmp);
				tmp = res;
				res = ft_joinchar(tmp, ' ');
				free(tmp);
			}
			else
			{
				tmp = res;
				res = ft_joinchar(tmp, line[i]);
				free(tmp);
			}
		}
		i++;
	}
	return (res);
}

unsigned int	wordlen(char *line)
{
	unsigned int	i;

	i = 0;
	if (line[0] == QUOTE)
	{
		i++;
		while (line[i] != QUOTE && line[i])
			i++;
		if (line[i])
			i++;
	}
	else if (line[0] == DQUOTE)
	{
		i++;
		while (line[i] != DQUOTE && line[i])
			i++;
		if (line[i])
			i++;
	}
	else
		while (line[i] != SPACE && line[i])
		{
			if (line[i] == QUOTE)
			{
				i++;
				while (line[i] != QUOTE && line[i])
					i++;
			}
			else if (line[i] == DQUOTE)
			{
				i++;
				while (line[i] != DQUOTE && line[i])
					i++;
			}
			i++;
		}
	return (i);
}

int	spacecount(char *line)
{
	int	nb;

	nb = 0;
	while (line[nb] && line[nb] == SPACE)
		nb++;
	return (nb);
}

char	**commandsplit(char *line)
{
	char	**split;
	int		i;
	size_t	j;
	int		wordcount;
	int		len;

	wordcount = counttoken(line);
	if (wordcount == -1 || !wordcount)
		return (NULL);
	split = ft_calloc(wordcount + 1, sizeof (char *));
	j = 0;
	i = 0;
	while (i < wordcount && j < ft_strlen(line))
	{
		j += spacecount(&line[j]);
		len = wordlen(&line[j]);
		split[i] = ft_substr(line, j, len);
		j += len;
		i++;
	}
	split[i] = NULL;
	return (split);
}

void	printredir(t_redir *redir)
{
	t_redir	*current;

	current = redir;
	while (current)
	{
		printf("redir == %s | arg == %s | %p\n", current->redir, current->arg, current->next);
		current = current->next;
	}
}

void	printlink(t_link *cmd)
{
	int		i;
	t_link	*current;

	current = cmd;
	while (current)
	{
		i = 0;
		while (current->command[i])
		{
			printf("%s\n", current->command[i]);
			i++;
		}
		printredir(current->redir);
		printf("-------------------------------\n");
		current = current->next;
	}
}

void	printsplit(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		printf("%s\n", split[i]);
		i++;
	}
}

void	echo_control_seq(t_bool c)
{
	struct termios	conf;

	ioctl(ttyslot(), TIOCGETA, &conf);
	if (c == true)
		conf.c_lflag |= ECHOCTL;
	else if (c == false)
		conf.c_lflag &= ~(ECHOCTL);
	ioctl(ttyslot(), TIOCSETA, &conf);
}

void	signalhandler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		if (!g_signal.childpid)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
	else if (sig == SIGQUIT && !g_signal.childpid)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		printf("Quit: 3\n");
}

t_redir	*redirinit(char *redir, char *arg)
{
	t_redir	*node;

	node = ft_calloc(1, sizeof (t_redir));
	node->redir = ft_strdup(redir);
	node->arg = ft_strdup(arg);
	node->next = NULL;
	return (node);
}

void	rediradd(t_redir **head, t_redir *new)
{
	t_redir	*current;

	if (!head || !(*head))
		*head = new;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

void	redirmaker(t_link *cmd)
{
	int		i;
	t_link	*current;

	current = cmd;
	while (current)
	{
		current->redir = NULL;
		i = -1;
		while (current->command[++i])
		{
			if (!ft_strcmp(current->command[i], ">") || !ft_strcmp(current->command[i], ">>")
				|| !ft_strcmp(current->command[i], "<") || !ft_strcmp(current->command[i], "<<"))
			{
				rediradd(&current->redir, redirinit(current->command[i], current->command[i + 1]));
				i++;
			}
		}
		current = current->next;
	}
}

char	**joinstr(char **split, char *str)
{
	int		i;
	char	**join;

	join = ft_calloc(splitlen(split) + 2, sizeof (char *));
	i = 0;
	while (split[i])
	{
		join[i] = ft_strdup(split[i]);
		i++;
	}
	join[i] = ft_strdup(str);
	return (join);
}

char	**redirremover(char **tokens)
{
	int		i;
	int		count;
	char	**tmp;
	char	**res;

	res = ft_calloc(1, sizeof (char *));
	count = 0;
	i = 0;
	while (tokens && tokens[i])
	{
		if (ft_strcmp(tokens[i], ">") && ft_strcmp(tokens[i], ">>")
			&& ft_strcmp(tokens[i], "<") && ft_strcmp(tokens[i], "<<"))
		{
			tmp = res;
			res = joinstr(tmp, tokens[i]);
			free(tmp);
		}
		else
			i++;
		i++;
	}
	return (res);
}

void	trimtokens(char **tokens)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tokens && tokens[i])
	{
		tmp = tokens[i];
		tokens[i] = ft_trimquotes(tmp);
		free(tmp);
		i++;
	}
}

void	cleancommand(t_link *cmd)
{
	t_link	*current;	

	current = cmd;
	while (current)
	{
		current->command = redirremover(current->command);
		trimtokens(current->command);
		current = current->next;
	}
}

int	main(int ac, char **av, char **ev)
{
	char	*line;
	char	*tmp;
	char	**tokens;
	t_all	all;

	(void)ac;
	(void)av;
	all.headenv = envmaker(ev);
	signal(SIGINT, signalhandler);
	signal(SIGQUIT, signalhandler);
	while (1)
	{
		echo_control_seq(false);
		g_signal.childpid = 0;
		g_signal.all = &all;
		line = readline("minishell> ");
		if (!line)
		{
			ft_putstrnl("exit");
			exit(0);
		}
		add_history(line);
		tmp = line;
		line = ft_strtrim(line, " ");
		free(tmp);
		if (checkerror(line) == true)
		{
			tmp = line;
			line = parsenv(&all, tmp, all.headenv);
			free(tmp);
			tokens = parstoken(line);
			if (tokens && splitlen(tokens))
			{
				all.headcmd = parspipe(tokens);
				redirmaker(all.headcmd);
				all.headcmd->path_bis = ft_getenv("PATH", all.headenv);
				cleancommand(all.headcmd);
				minishell(&all, all.headcmd);
				while(wait(NULL) > 0)
					;
			}
		}
		else
			ft_puterr("parse error\n");
	}
	return (0);
}
