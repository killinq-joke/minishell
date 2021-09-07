/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 18:20:44 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/03 18:14:06by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsenv1(t_all *all, char *line, t_env *env, t_pars *p)
{
	if (line[p->i])
	{
		p->j = 0;
		while (line[p->i + p->j + 1] && line[p->i + p->j + 1] != SPACE
			&& line[p->i + p->j + 1]
			!= QUOTE && line[p->i + p->j + 1] != DQUOTE)
			p->j++;
		p->name = ft_substr(&line[1], p->i, p->j);
		if (!ft_strlen(p->name))
		{
			p->tmp = p->res;
			p->res = ft_strjoin(p->tmp, "$");
			free(p->tmp);
		}
		else if (!ft_strcmp(p->name, "?"))
			parsenv11(all, p);
		else
			parsenv12(env, p);
		free(p->name);
		p->i += p->j;
	}
}

void	parsenv2(char *line, t_pars *p)
{
	if (line[p->i] == DQUOTE)
		p->indquote = !p->indquote;
	if ((!ft_strncmp(">>", &line[p->i], 2)
			|| !ft_strncmp("<<", &line[p->i], 2)) && !p->indquote)
	{
		p->res = joinandfree(p->res, ' ');
		p->res = joinandfree(p->res, line[p->i++]);
		p->res = joinandfree(p->res, line[p->i]);
		p->res = joinandfree(p->res, ' ');
	}
	else if (ft_isin("><|", line[p->i]) && !p->indquote)
	{
		p->res = joinandfree(p->res, ' ');
		p->res = joinandfree(p->res, line[p->i]);
		p->res = joinandfree(p->res, ' ');
	}
	else
		p->res = joinandfree(p->res, line[p->i]);
}

void	parsenv0(char *line, t_pars *p)
{
	p->tmp = p->res;
	p->res = ft_joinchar(p->tmp, line[p->i]);
	free(p->tmp);
	p->i++;
	while (line[p->i] && line[p->i] != QUOTE)
	{
		p->tmp = p->res;
		p->res = ft_joinchar(p->tmp, line[p->i]);
		free(p->tmp);
		p->i++;
	}
	if (line[p->i] && line[p->i] == QUOTE)
	{
		p->tmp = p->res;
		p->res = ft_joinchar(p->tmp, line[p->i]);
		free(p->tmp);
	}
}

char	*parsenv(t_all *all, char *line, t_env *env)
{
	t_pars	p;

	p.res = ft_calloc(1, sizeof (char));
	p.i = 0;
	p.indquote = false;
	while (line[p.i])
	{
		if (line[p.i] && line[p.i] == QUOTE)
			parsenv0(line, &p);
		else if (line[p.i] && line[p.i] == '$')
			parsenv1(all, line, env, &p);
		else
			parsenv2(line, &p);
		p.i++;
	}
	return (p.res);
}
