/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legunshi <legunshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 20:02:57 by legunshi          #+#    #+#             */
/*   Updated: 2021/03/21 20:31:28 by legunshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	we_ea_borders(t_all *all)
{
	int	s;
	int	v;

	s = 0;
	while (s < all->map.rows)
	{
		v = 0;
		while (all->map.map[s][v] == ' ')
			v++;
		if (all->map.map[s][v] != '1')
			close_prog(all, 22);
		s++;
	}
	s = 0;
	v = 0;
	while (s < all->map.rows)
	{
		while (all->map.map[s][v] && all->map.map[s][v] != '\0')
			v++;
		v--;
		if (all->map.map[s][v] != '1' && all->map.map[s][v] != ' ')
			close_prog(all, 27);
		s++;
		v = 0;
	}
}

void	no_borders(t_all *all)
{
	int	v;

	v = 0;
	while (all->map.map[0][v])
	{
		if (all->map.map[0][v] != '1' && all->map.map[0][v] != ' ')
			close_prog(all, 28);
		v++;
	}
	v = 0;
	while (all->map.map[1][v])
	{
		if (all->map.map[1][v] == 'N' || all->map.map[1][v] == 'S' ||
			all->map.map[1][v] == 'E' || all->map.map[1][v] == 'W' ||
			all->map.map[1][v] == '0' || all->map.map[1][v] == '2')
		{
			if (all->map.map[0][v] != '1')
				close_prog(all, 28);
		}
		v++;
	}
}

void	so_borders(t_all *all)
{
	int	v;

	v = -1;
	while (++v < all->map.col)
	{
		if (all->map.map[all->map.rows - 1][v] != '1' &&
			all->map.map[all->map.rows - 1][v] != ' ' &&
			all->map.map[all->map.rows - 1][v] != '\0')
			close_prog(all, 29);
	}
	v = 0;
	while (all->map.map[all->map.rows - 2][v])
	{
		if (all->map.map[all->map.rows - 2][v] == 'N' ||
			all->map.map[all->map.rows - 2][v] == 'S' ||
			all->map.map[all->map.rows - 2][v] == 'E' ||
			all->map.map[all->map.rows - 2][v] == 'W' ||
			all->map.map[all->map.rows - 2][v] == '0' ||
			all->map.map[all->map.rows - 2][v] == '2')
		{
			if (all->map.map[all->map.rows - 1][v] != '1')
				close_prog(all, 29);
		}
		v++;
	}
}

void	player_pos(t_all *all, int s, int v)
{
	if ((all->map.map[s][v] >= 'A' && all->map.map[s][v] <= 'Z') &&
		all->map.map[s][v] != 'N' && all->map.map[s][v] != 'S' &&
		all->map.map[s][v] != 'E' && all->map.map[s][v] != 'W')
		close_prog(all, 32);
	if (all->map.map[s][v] >= 'a' && all->map.map[s][v] <= 'z')
		close_prog(all, 32);
	if ((all->map.map[s][v] == 'N' || all->map.map[s][v] == 'S' ||
		all->map.map[s][v] == 'E' || all->map.map[s][v] == 'W') &&
		all->ident.plr == 0)
	{
		all->ident.plr = 1;
		all->rayc.pos_x = s + 0.5;
		all->rayc.pos_y = v + 0.5;
		all->map.orientation = all->map.map[s][v];
	}
	else if ((all->map.map[s][v] == 'N' || all->map.map[s][v] == 'S' ||
		all->map.map[s][v] == 'E' || all->map.map[s][v] == 'W') &&
		all->ident.plr == 1)
		close_prog(all, 21);
}

void	mapchecking(t_all *all)
{
	int	s;
	int	v;

	s = 0;
	v = 0;
	while (s < all->map.rows)
	{
		while (all->map.map[s][v])
		{
			if (all->map.map[s][v] != '1' && all->map.map[s][v] != '0' &&
			all->map.map[s][v] != '2' && all->map.map[s][v] != ' ' &&
			all->map.map[s][v] != 'N' && all->map.map[s][v] != 'S' &&
			all->map.map[s][v] != 'E' && all->map.map[s][v] != 'W')
				close_prog(all, 34);
			player_pos(all, s, v);
			if (all->map.map[s][v] == '2')
				all->rayc.spr_num += 1;
			v++;
		}
		s++;
		v = 0;
	}
	if (all->ident.plr != 1)
		close_prog(all, 37);
	check_all_borders(all);
}
