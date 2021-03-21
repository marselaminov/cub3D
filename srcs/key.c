/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legunshi <legunshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 19:34:17 by legunshi          #+#    #+#             */
/*   Updated: 2021/03/21 19:58:44 by legunshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		keyexit(t_all *all)
{
	close_prog(all, 0);
	return (0);
}

int		keyrelease(int key, t_all *all)
{
	if (key == W)
		all->move.up = 0;
	if (key == S)
		all->move.down = 0;
	if (key == D)
		all->move.right = 0;
	if (key == A)
		all->move.left = 0;
	if (key == R)
		all->move.rot_right = 0;
	if (key == L)
		all->move.rot_left = 0;
	if (key == E)
		keyexit(all);
	return (0);
}

int		keypress(int key, t_all *all)
{
	if (key == W)
		all->move.up = 1;
	if (key == S)
		all->move.down = 1;
	if (key == D)
		all->move.right = 1;
	if (key == A)
		all->move.left = 1;
	if (key == R)
		all->move.rot_right = 1;
	if (key == L)
		all->move.rot_left = 1;
	return (0);
}

void	rotate_right(t_all *all)
{
	if (all->move.rot_right == 1)
	{
		all->move.olddir_x = all->rayc.dir_x;
		all->rayc.dir_x = all->rayc.dir_x * cos(all->move.rot_speed)
			- all->rayc.dir_y * sin(all->move.rot_speed);
		all->rayc.dir_y = all->move.olddir_x * sin(all->move.rot_speed)
			+ all->rayc.dir_y * cos(all->move.rot_speed);
		all->move.oldplane_x = all->rayc.plane_x;
		all->rayc.plane_x = all->rayc.plane_x * cos(all->move.rot_speed)
			- all->rayc.plane_y * sin(all->move.rot_speed);
		all->rayc.plane_y = all->move.oldplane_x * sin(all->move.rot_speed)
			+ all->rayc.plane_y * cos(all->move.rot_speed);
	}
}

void	rotate_left(t_all *all)
{
	if (all->move.rot_left == 1)
	{
		all->move.olddir_x = all->rayc.dir_x;
		all->rayc.dir_x = all->rayc.dir_x * cos(-all->move.rot_speed)
			- all->rayc.dir_y * sin(-all->move.rot_speed);
		all->rayc.dir_y = all->move.olddir_x * sin(-all->move.rot_speed)
			+ all->rayc.dir_y * cos(-all->move.rot_speed);
		all->move.oldplane_x = all->rayc.plane_x;
		all->rayc.plane_x = all->rayc.plane_x * cos(-all->move.rot_speed)
			- all->rayc.plane_y * sin(-all->move.rot_speed);
		all->rayc.plane_y = all->move.oldplane_x * sin(-all->move.rot_speed)
			+ all->rayc.plane_y * cos(-all->move.rot_speed);
	}
}
