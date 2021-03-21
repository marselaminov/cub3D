/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legunshi <legunshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 21:09:42 by legunshi          #+#    #+#             */
/*   Updated: 2021/03/21 21:15:53 by legunshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	step_x(t_all *all)
{
	if (all->rayc.raydir_x < 0)
	{
		all->rayc.step_x = -1;
		all->rayc.sidedist_x = (all->rayc.pos_x - all->rayc.map_x) *
			all->rayc.deltdist_x;
	}
	else
	{
		all->rayc.step_x = 1;
		all->rayc.sidedist_x = (all->rayc.map_x + 1 - all->rayc.pos_x) *
			all->rayc.deltdist_x;
	}
}

void	step_y(t_all *all)
{
	if (all->rayc.raydir_y < 0)
	{
		all->rayc.step_y = -1;
		all->rayc.sidedist_y = (all->rayc.pos_y - all->rayc.map_y) *
			all->rayc.deltdist_y;
	}
	else
	{
		all->rayc.step_y = 1;
		all->rayc.sidedist_y = (all->rayc.map_y + 1 - all->rayc.pos_y) *
			all->rayc.deltdist_y;
	}
}

void	dda_init(t_all *all)
{
	all->rayc.hit = 0;
	while (all->rayc.hit == 0)
	{
		if (all->rayc.sidedist_x < all->rayc.sidedist_y)
		{
			all->rayc.sidedist_x += all->rayc.deltdist_x;
			all->rayc.map_x += all->rayc.step_x;
			all->rayc.side = 0;
		}
		else
		{
			all->rayc.sidedist_y += all->rayc.deltdist_y;
			all->rayc.map_y += all->rayc.step_y;
			all->rayc.side = 1;
		}
		if ((all->map.orientation == 'N' && all->map.map[all->rayc.map_x]
		[all->rayc.map_y] == ' ') || (all->map.orientation == 'S' &&
		all->map.map[all->rayc.map_x][all->rayc.map_y] == ' ') ||
		(all->map.orientation == 'W' && all->map.map[all->rayc.map_x]
		[all->rayc.map_y] == ' ') || (all->map.orientation == 'E' &&
			all->map.map[all->rayc.map_x][all->rayc.map_y] == ' '))
			close_prog(all, 23);
		if (all->map.map[all->rayc.map_x][all->rayc.map_y] == '1')
			all->rayc.hit = 1;
	}
}

void	len_of_the_ray(t_all *all)
{
	if (all->rayc.side == 0)
		all->rayc.perp_walldist = (all->rayc.map_x - all->rayc.pos_x +
			(1 - all->rayc.step_x) / 2) / all->rayc.raydir_x;
	else
		all->rayc.perp_walldist = (all->rayc.map_y - all->rayc.pos_y +
			(1 - all->rayc.step_y) / 2) / all->rayc.raydir_y;
}

void	init_raycast(t_all *all)
{
	int	w;
	int	h;

	w = 0;
	h = 0;
	while (w < all->map.width)
	{
		all->rayc.camera_x = 2 * w / (double)(all->map.width) - 1;
		all->rayc.raydir_x = all->rayc.dir_x + all->rayc.plane_x *
			all->rayc.camera_x;
		all->rayc.raydir_y = all->rayc.dir_y + all->rayc.plane_y *
			all->rayc.camera_x;
		all->rayc.deltdist_x = fabs(1 / all->rayc.raydir_x);
		all->rayc.deltdist_y = fabs(1 / all->rayc.raydir_y);
		all->rayc.map_x = (int)all->rayc.pos_x;
		all->rayc.map_y = (int)all->rayc.pos_y;
		step_x(all);
		step_y(all);
		dda_init(all);
		len_of_the_ray(all);
		drawn_on_screen(all, w, h);
		all->rays.dist_wall[w] = all->rayc.perp_walldist;
		w++;
	}
}
