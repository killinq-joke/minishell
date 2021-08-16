/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 19:57:44 by ztouzri           #+#    #+#             */
/*   Updated: 2021/08/16 09:43:51by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void	minishell(t_link *cmd)
//{
//	int		fd[2];
//	int		tmp;
//	t_link	*actuel;

//	actuel = cmd;
//	while (actuel)
//	{
//		if (actuel->next)
//		{
//			pipe(fd);
//			dup2(tmp, STDIN_FILENO);
//			dup2(fd[1], STDOUT_FILENO);
//			give_good_path(all);
//		}
//		else
//		{
//			dup2(tmp, STDIN_FILENO);
//			give_good_path(all);
//		}
//		actuel = actuel->next;
//	}
//}

void	minishell(t_all *all, t_link *cmd)
{
	t_link	*actuel;
	int		fd[2];
	int		tmp;

	(void)all;
	actuel = cmd;
	while (actuel)
	{
		if (actuel->next)
		{
			pipe(fd);
			if (fork() == 0)
			{
				dup2(tmp, STDIN_FILENO);
				dup2(fd[1], STDOUT_FILENO);
				give_good_path(all);
			}
			close(fd[1]);
			tmp = fd[0];
		}
		else
		{
			if (fork() == 0)
			{
				dup2(tmp, STDIN_FILENO);
				give_good_path(all);
			}
		}
		wait(0);
		actuel = actuel->next;
	}
}
