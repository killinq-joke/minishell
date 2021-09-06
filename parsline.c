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

int	counttoken(char *line)
{
	int	i;
	int	count;
	int	nbquote;

	nbquote = 0;	
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
			if (line[i] == DQUOTE)
				nbquote++;
			while (line[i])
			{
				if (line[i] == DQUOTE)
					nbquote++;
				if ((line[i] == DQUOTE && (line[i + 1] == SPACE || !line[i + 1])))
					break ;
				i++;
			}
			if (!(nbquote % 2))
			{
				ft_puterr("error: unclosed dquotes not supported\n");
				return (-1);
			}
			count++;
		}
		if (line[i] == QUOTE)
		{
			i++;
			while (line[i])
			{
				if (line[i] == QUOTE)
					nbquote++;
				if ((line[i] == QUOTE && (line[i + 1] == SPACE || !line[i + 1])))
					break ;
				i++;
			}
			if (!(nbquote % 2))
			{
				ft_puterr("error: unclosed quotes not supported\n");
				return (-1);
			}
			count++;
		}
		if (!line[i])
			break ;
		i++;
		printf("nbquote === %d\n", nbquote);
		nbquote = 0;
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
			if (line[i])
			{
				j = 0;
				while (line[i + j + 1] && line[i + j + 1] != SPACE
					&& line[i + j + 1] != QUOTE && line[i + j + 1] != DQUOTE)
					j++;
				name = ft_substr(&line[1], i, j);
				if (!ft_strlen(name))
				{
					tmp = res;
					res = ft_strjoin(tmp, "$");
					free(tmp);
				}
				else if (!ft_strcmp(name, "?"))
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
