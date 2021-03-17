#include "../includes/cub3d.h"

void		step_x(t_all *all)
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

void		step_y(t_all *all)
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
		if (all->map.map[all->rayc.map_x][all->rayc.map_y] == '1')
			all->rayc.hit = 1;
	}
}

void	len_of_the_ray(t_all *all)
{
	if (all->rayc.side == 0)
		all->rayc.perp_walldist = (all->rayc.map_x - all->rayc.pos_x + 
		(1 - all->rayc.step_x) / 2) / all->rayc.raydir_x;//number of squares the ray has crossed in X direction
	else
		all->rayc.perp_walldist = (all->rayc.map_y - all->rayc.pos_y + 
		(1 - all->rayc.step_y) / 2) / all->rayc.raydir_y;//number of squares the ray has crossed in Y direction
}

void	init_raycast(t_all *all)
{
	int	w;
	int	h;

	w = 0;
	h = 0;
	while (w < all->map.width)
	{
		all->rayc.camera_x = 2 * w / (double)(all->map.width) - 1;//x-coordinate in camera space
		all->rayc.raydir_x = all->rayc.dir_x + all->rayc.plane_x * all->rayc.camera_x;//x ray position and direction
		all->rayc.raydir_y = all->rayc.dir_y + all->rayc.plane_y * all->rayc.camera_x;//y ray position and direction
		all->rayc.deltdist_x = fabs(1 / all->rayc.raydir_x);//length of ray from current position to next x-side
		all->rayc.deltdist_y = fabs(1 / all->rayc.raydir_y);//length of ray from current position to next y-side
		all->rayc.map_x = (int)all->rayc.pos_x;//box of the map we're in
		all->rayc.map_y = (int)all->rayc.pos_y;
		step_x(all);//calculate stepx and initial sideDistx
		step_y(all);//calculate stepy and initial sideDisty
		dda_init(all);/*Digital Differential Analyzer (цифровой дифференциальный анализатор) — 
		вычислительное устройство, применявшееся для генерации векторов.*/
		len_of_the_ray(all);/*сalculate distance projected on camera direction (camera plane, not Euclidean distance,
		because Euclidean distance will give fisheye effect)*/
		drawn_on_screen(all, w, h);
		//SET THE ZBUFFER FOR THE SPRITE CASTING
		all->rays.dist_wall[w] = all->rayc.perp_walldist;//perpendicular distance is used
		w++;
	}
}
