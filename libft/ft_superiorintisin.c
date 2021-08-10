/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_superiorintisin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 17:31:38 by ztouzri           #+#    #+#             */
/*   Updated: 2021/06/01 19:09:27 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_superiorintisin(int *tab, int size, int num)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (tab[i] >= num)
			return (1);
		i++;
	}
	return (0);
}

int	ft_strictsuperiorintisin(int *tab, int size, int num)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (tab[i] > num)
			return (1);
		i++;
	}
	return (0);
}
