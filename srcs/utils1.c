/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legunshi <legunshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 20:35:34 by legunshi          #+#    #+#             */
/*   Updated: 2021/03/22 20:38:18 by legunshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		cubcheck(char *s)
{
	int	i;

	i = 0;
	while (s != 0 && s[i] != 0)
	{
		if (s[i] == '.' && s[i + 1] == 'c' && s[i + 2] == 'u' &&
			s[i + 3] == 'b' && s[i + 4] == '\0')
			return (0);
		i++;
	}
	return (1);
}

int		savecheck(char *arg, char *save)
{
	int	i;

	i = 0;
	while (arg[i] == save[i])
	{
		if (arg[i] == '\0' && save[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int		cub_atoi(char *line, int *i)
{
	int	num;

	num = 0;
	while (line[*i] == ' ')
		i++;
	while (line[*i] >= '0' && line[*i] <= '9')
	{
		num = num * 10 + line[*i] - '0';
		if (num > 1000000)
			num = 1000000;
		(*i)++;
	}
	return (num);
}

void	get_screen_size(t_all *all)
{
	int	w;
	int	h;

	w = 0;
	h = 0;
	mlx_get_screen_size(all->mlx.mlx, &w, &h);
	if (all->map.width > w)
		all->map.width = w;
	if (all->map.height > h)
		all->map.height = h;
}

void	spr_in_map(t_all *all)
{
	int	width;
	int	height;
	int	i;

	height = 0;
	i = 0;
	while (height < all->map.rows)
	{
		width = 0;
		while (width < all->map.col)
		{
			if (all->map.map[height][width] == '2')
			{
				all->spr[i].x = height + 0.5;
				all->spr[i].y = width + 0.5;
				i++;
			}
			width++;
		}
		height++;
	}
}
