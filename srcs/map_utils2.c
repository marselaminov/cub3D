/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legunshi <legunshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 20:28:19 by legunshi          #+#    #+#             */
/*   Updated: 2021/03/21 20:34:52 by legunshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	map_borders1(t_all *all)
{
	int	s;
	int	v;

	s = 1;
	while (s < all->map.rows - 1)
	{
		v = 1;
		while (all->map.map[s][v])
		{
			if (all->map.map[s][v] == ' ' &&
			((all->map.map[s][v - 1] == '0' && v != 0) ||
			(all->map.map[s][v + 1] == '0' && v != all->map.col - 1)
			|| all->map.map[s - 1][v] == '0'
				|| all->map.map[s + 1][v] == '0'))
				close_prog(all, 23);
			v++;
		}
		s++;
	}
}

void	map_borders2(t_all *all)
{
	int	s;
	int	v;

	s = 1;
	while (s < all->map.rows - 1)
	{
		v = 1;
		while (all->map.map[s][v])
		{
			if ((all->map.map[s][v] == '0' || all->map.map[s][v] == '2' ||
			all->map.map[s][v] == 'N' || all->map.map[s][v] == 'S' ||
			all->map.map[s][v] == 'E' || all->map.map[s][v] == 'W') &&
			((all->map.map[s][v - 1] == ' ' && v != 0) ||
			(all->map.map[s][v + 1] == ' ' && v != all->map.col - 1) ||
			(all->map.map[s - 1][v - 1] == ' ' && v != 0) ||
				(all->map.map[s - 1][v + 1] == ' ' && v != all->map.col - 1)))
				close_prog(all, 23);
			v++;
		}
		s++;
	}
}

void	map_borders3(t_all *all)
{
	int	s;
	int	v;

	s = 1;
	while (s < all->map.rows - 1)
	{
		v = 1;
		while (all->map.map[s][v])
		{
			if ((all->map.map[s][v] == 'N' || all->map.map[s][v] == 'S' ||
			all->map.map[s][v] == 'E' ||
			all->map.map[s][v] == 'W') && ((all->map.map[s][v - 1] == ' ' &&
			v != 0) || (all->map.map[s][v + 1] == ' ' &&
			v != all->map.col - 1) || all->map.map[s - 1][v] == ' ' ||
				all->map.map[s + 1][v] == ' '))
				close_prog(all, 23);
			v++;
		}
		s++;
	}
}

void	map_borders4(t_all *all)
{
	int	s;
	int	v;

	s = 1;
	while (s < all->map.rows - 1)
	{
		v = 1;
		while (all->map.map[s][v])
		{
			if ((all->map.map[s][v] == '0' || all->map.map[s][v] == '2' ||
			all->map.map[s][v] == 'N' || all->map.map[s][v] == 'S' ||
			all->map.map[s][v] == 'E' || all->map.map[s][v] == 'W') &&
			((all->map.map[s][v - 1] == '\0' && v != 0) ||
			(all->map.map[s][v + 1] == '\0' && v != all->map.col - 1) ||
			all->map.map[s - 1][v] == '\0' || all->map.map[s + 1][v] == '\0' ||
			(all->map.map[s - 1][v - 1] == ' ' && v != 0) ||
			(all->map.map[s - 1][v + 1] == ' ' && v != all->map.col - 1) ||
			(all->map.map[s + 1][v - 1] == ' ' && v != 0) ||
				(all->map.map[s + 1][v + 1] == ' ' && v != all->map.col - 1)))
				close_prog(all, 23);
			v++;
		}
		s++;
	}
}

void	check_all_borders(t_all *all)
{
	map_borders1(all);
	map_borders2(all);
	map_borders3(all);
	map_borders4(all);
	we_ea_borders(all);
	no_borders(all);
	so_borders(all);
}
