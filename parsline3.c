/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 18:20:44 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/08 10:27:26 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*joinandfree(char *line, char c)
{
	char	*tmp;

	tmp = line;
	line = ft_joinchar(tmp, c);
	free(tmp);
	return (line);
}

void	parsenv11(t_all *all, t_pars *p)
{
	p->tmp = p->res;
	p->tmp1 = ft_itoa(all->exit_status);
	p->res = ft_strjoin(p->tmp, p->tmp1);
	free(p->tmp1);
	free(p->tmp);
}

void	parsenv12(t_env *env, t_pars *p)
{
	p->tmp = p->res;
	p->tmp1 = ft_getenv(p->name, env);
	p->res = ft_strjoin(p->tmp, p->tmp1);
	free(p->tmp1);
	free(p->tmp);
}
