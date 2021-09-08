/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 10:29:57 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/08 10:29:58 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	minishell2(char *tmp, char *line, t_all *all)
{
	char	**tokens;

	tmp = line;
	line = parsenv(all, tmp, all->headenv);
	free(tmp);
	tokens = commandsplit(line);
	free(line);
	if (tokens && splitlen(tokens))
	{
		all->headcmd = parspipe(tokens);
		redirmaker(all->headcmd);
		all->headcmd->path_bis = ft_getenv("PATH", all->headenv);
		cleancommand(all->headcmd);
		minishell(all, all->headcmd);
		while (wait(NULL) > 0)
			;
		freelink(all->headcmd);
	}
}

void	complete_minishell(t_all *all)
{
	char	*line;
	char	*tmp;	

	while (1)
	{
		echo_control_seq(false);
		g_signal.childpid = 0;
		g_signal.all = all;
		line = readline("minishell> ");
		if (!line)
		{
			ft_putstrnl("exit");
			close(STDIN_FILENO);
			exit(0);
		}
		add_history(line);
		tmp = line;
		line = ft_strtrim(line, " ");
		free(tmp);
		if (checkerror(line))
			minishell2(tmp, line, all);
		else
			ft_puterr("parse error\n");
	}
}
