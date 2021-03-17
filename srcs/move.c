#include "../includes/cub3d.h"

void	move_r_l(t_all *all)
{
	if (all->move.right == 1)
	{
		if (all->map.map[(int)(all->rayc.pos_y)][(int)(all->rayc.plane_x * all->move.move_speed 
			+ all->rayc.pos_x)] != '1' && all->map.map[(int)(all->rayc.pos_y)]
			[(int)(all->rayc.plane_x * all->move.move_speed + all->rayc.pos_x)] != '2')
			all->rayc.pos_x += all->rayc.plane_x * all->move.move_speed;
		if (all->map.map[(int)(all->rayc.pos_y + all->rayc.plane_y * all->move.move_speed)]
			[(int)(all->rayc.pos_x)] != '1' && all->map.map[(int)(all->rayc.pos_y + 
			all->rayc.plane_y * all->move.move_speed)][(int)(all->rayc.pos_x)] != '2')
			all->rayc.pos_y += all->rayc.plane_y * all->move.move_speed;
	}
	if (all->move.left == 1)
	{
		if (all->map.map[(int)(all->rayc.pos_y)][(int)(all->rayc.pos_x - all->rayc.plane_x *
			all->move.move_speed)] != '1' && all->map.map[(int)(all->rayc.pos_y)][(int)
			(all->rayc.pos_x - all->rayc.plane_x * all->move.move_speed)] != '2')
			all->rayc.pos_x -= all->rayc.plane_x * all->move.move_speed;
		if (all->map.map[(int)(all->rayc.pos_y - all->rayc.plane_y * all->move.move_speed)]
			[(int)(all->rayc.pos_x)] != '1' && all->map.map[(int)(all->rayc.pos_y - 
			all->rayc.plane_y * all->move.move_speed)][(int)(all->rayc.pos_x)] != '2')
			all->rayc.pos_y -= all->rayc.plane_y * all->move.move_speed;
	}
}

void	move_up_down(t_all *all)
{
	if (all->move.up == 1)
	{
		if (all->map.map[(int)(all->rayc.pos_x + all->rayc.dir_x 
			* all->move.move_speed)][(int)(all->rayc.pos_y)] != '1' && all->map.map
			[(int)(all->rayc.pos_x + all->rayc.dir_x * all->move.move_speed)][(int)(all->rayc.pos_y)] != '2')
			all->rayc.pos_x += all->rayc.dir_x * all->move.move_speed;
		if (all->map.map[(int)(all->rayc.pos_x)][(int)(all->rayc.pos_y + all->rayc.dir_y * all->move.move_speed)]
			 != '1' && all->map.map[(int)(all->rayc.pos_x)][(int)(all->rayc.pos_y + 
			all->rayc.dir_y * all->move.move_speed)] != '2')
			all->rayc.pos_y += all->rayc.dir_y * all->move.move_speed;
	}
	if (all->move.down == 1)
	{
		if (all->map.map[(int)(all->rayc.pos_x - all->rayc.dir_x 
			* all->move.move_speed)][(int)(all->rayc.pos_y)] != '1' && all->map.map
			[(int)(all->rayc.pos_x - all->rayc.dir_x * all->move.move_speed)][(int)(all->rayc.pos_y)] != '2')
			all->rayc.pos_x -= all->rayc.dir_x * all->move.move_speed;
		if (all->map.map[(int)(all->rayc.pos_x)][(int)(all->rayc.pos_y - all->rayc.dir_y * all->move.move_speed)]
			 != '1' && all->map.map[(int)(all->rayc.pos_x)][(int)(all->rayc.pos_y - 
			all->rayc.dir_y * all->move.move_speed)] != '2')
			all->rayc.pos_y -= all->rayc.dir_y * all->move.move_speed;
	}
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

int		move_plr(t_all *all)
{
	all->move.move_speed = 0.1;
	all->move.rot_speed = 0.1;
	if (all->move.up == 1 || all->move.down == 1)
		move_up_down(all);
	if (all->move.right == 1 || all->move.left == 1)	
		move_r_l(all);
	if (all->move.rot_right == 1)
		rotate_right(all);
	if (all->move.rot_left == 1)
		rotate_left(all);
	launch_prog(all);
	return (0);
}