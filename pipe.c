/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 19:57:44 by ztouzri           #+#    #+#             */
/*   Updated: 2021/08/14 20:13:10 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    minishell(t_link *cmd)
{
    int fd[2];
    int tmp;
    t_link *actuel;

    actuel = cmd;

    while(actuel)
    {
        if (actuel->next)
        {
            pipe(fd);
            dup2(tmp, STDIN_FILENO);
            dup2(fd[1], STDOUT_FILENO);
            give_good_path(cmd);
        }
        else
        {
            dup2(tmp, STDIN_FILENO); 
            give_good_path(cmd); 
        }
        actuel = actuel->next;
    }
    
}