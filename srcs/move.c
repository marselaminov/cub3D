/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legunshi <legunshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 19:45:34 by legunshi          #+#    #+#             */
/*   Updated: 2021/03/21 19:57:18 by legunshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_r(t_all *all)
{
	if (all->move.right == 1)
	{
		if (all->map.map[(int)(all->rayc.dir_y * all->move.move_speed +
			all->rayc.pos_x)][(int)(all->rayc.pos_y)] != '1' &&
			all->map.map[(int)(all->rayc.dir_y * all->move.move_speed
			+ all->rayc.pos_x)][(int)(all->rayc.pos_y)] != '2')
			all->rayc.pos_x += all->rayc.dir_y * all->move.move_speed;
		if (all->map.map[(int)(all->rayc.pos_x)][(int)(all->rayc.pos_y -
			all->rayc.dir_x * all->move.move_speed)] != '1' &&
			all->map.map[(int)(all->rayc.pos_x)][(int)(all->rayc.pos_y -
			all->rayc.dir_x * all->move.move_speed)] != '2')
			all->rayc.pos_y -= all->rayc.dir_x * all->move.move_speed;
	}
}

void	move_l(t_all *all)
{
	if (all->move.left == 1)
	{
		if (all->map.map[(int)(all->rayc.pos_x - all->rayc.dir_y *
			all->move.move_speed)][(int)(all->rayc.pos_y)] != '1' &&
			all->map.map[(int)(all->rayc.pos_x - all->rayc.dir_y *
			all->move.move_speed)][(int)(all->rayc.pos_y)] != '2')
			all->rayc.pos_x -= all->rayc.dir_y * all->move.move_speed;
		if (all->map.map[(int)(all->rayc.pos_x)][(int)(all->rayc.pos_y +
			all->rayc.dir_x * all->move.move_speed)] != '1' &&
			all->map.map[(int)(all->rayc.pos_x)][(int)(all->rayc.pos_y +
			all->rayc.dir_x * all->move.move_speed)] != '2')
			all->rayc.pos_y += all->rayc.dir_x * all->move.move_speed;
	}
}

void	move_up(t_all *all)
{
	if (all->move.up == 1)
	{
		if (all->map.map[(int)(all->rayc.pos_x + all->rayc.dir_x
			* all->move.move_speed)][(int)(all->rayc.pos_y)] != '1' &&
			all->map.map[(int)(all->rayc.pos_x + all->rayc.dir_x *
			all->move.move_speed)][(int)(all->rayc.pos_y)] != '2')
			all->rayc.pos_x += all->rayc.dir_x * all->move.move_speed;
		if (all->map.map[(int)(all->rayc.pos_x)][(int)(all->rayc.pos_y +
			all->rayc.dir_y * all->move.move_speed)] != '1' &&
			all->map.map[(int)(all->rayc.pos_x)][(int)(all->rayc.pos_y +
			all->rayc.dir_y * all->move.move_speed)] != '2')
			all->rayc.pos_y += all->rayc.dir_y * all->move.move_speed;
	}
}

void	move_down(t_all *all)
{
	if (all->move.down == 1)
	{
		if (all->map.map[(int)(all->rayc.pos_x - all->rayc.dir_x
			* all->move.move_speed)][(int)(all->rayc.pos_y)] != '1'
			&& all->map.map[(int)(all->rayc.pos_x - all->rayc.dir_x *
			all->move.move_speed)][(int)(all->rayc.pos_y)] != '2')
			all->rayc.pos_x -= all->rayc.dir_x * all->move.move_speed;
		if (all->map.map[(int)(all->rayc.pos_x)][(int)(all->rayc.pos_y -
			all->rayc.dir_y * all->move.move_speed)] != '1' &&
			all->map.map[(int)(all->rayc.pos_x)][(int)(all->rayc.pos_y -
			all->rayc.dir_y * all->move.move_speed)] != '2')
			all->rayc.pos_y -= all->rayc.dir_y * all->move.move_speed;
	}
}

int		move_plr(t_all *all)
{
	all->move.move_speed = 0.1;
	all->move.rot_speed = 0.1;
	if (all->move.up == 1)
		move_up(all);
	if (all->move.down == 1)
		move_down(all);
	if (all->move.right == 1)
		move_r(all);
	if (all->move.left == 1)
		move_l(all);
	if (all->move.rot_right == 1)
		rotate_right(all);
	if (all->move.rot_left == 1)
		rotate_left(all);
	launch_prog(all);
	return (0);
}
