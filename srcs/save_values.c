/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legunshi <legunshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 21:16:23 by legunshi          #+#    #+#             */
/*   Updated: 2021/03/21 21:30:14 by legunshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*save_text(t_all *all, char *line, int i)
{
	char	*text;
	
	if ((line[i] >= 'a' && line[i] <= 'z') || 
		(line[i] >= 'A' && line[i] <= 'Z'))
		i++;
	if ((line[i] >= 'a' && line[i] <= 'z') || 
		(line[i] >= 'A' && line[i] <= 'Z'))
		i++;
	if (line[i] != ' ')
		close_prog(all, 25);
	while (line[i] == ' ')
		i++;
	text = ft_strdup(&line[i]);
	return (text);
}

void	get_map_memory(t_all *all)
{
	int	i;
	int	columns;

	i = 0;
	columns = 0;
	while (all->map.tmp[i])
	{
		if (all->map.tmp[i] == '\n')
		{
			if (all->map.col < columns)
				all->map.col = columns - 1;
			columns = 0;
		}
		i++;
		columns++;
	}
	if (!(all->map.map = malloc(sizeof(char*) * (all->map.rows + 1))))
		close_prog(all, 1);
	i = 0;
	while (i < all->map.rows)
	{
		if (!(all->map.map[i] = ft_calloc(sizeof(char), (all->map.col + 1))))
			close_prog(all, 1);
		i++;
	}
}

void	mapsaving(t_all *all)
{
	int	a;
	int	b;
	int	c;

	get_map_memory(all);
	a = 0;
	b = 0;
	c = 0;
	while (all->map.tmp[c])
	{
		if (all->map.tmp[c] != '\n')
		{
			all->map.map[a][b] = all->map.tmp[c];
			b++;
		}
		else
		{
			all->map.map[a][b] = '\0';
			a++;
			b = 0;
		}
		c++;
	}
	all->map.map[all->map.rows] = NULL;
}