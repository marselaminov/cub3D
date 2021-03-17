#include "../includes/cub3d.h"

void			sort_spr(t_all *all)
{
	int			tmp;
	int			i;
	int			j;
	int			sw;

	i = 0;
	while (i < all->rayc.spr_num - 1)
	{
		j = i + 1;
		while (j < all->rayc.spr_num)
		{
			if (all->spr[i].d < all->spr[j].d)
			{
				tmp = all->spr[i].d;
				all->spr[i].d = all->spr[j].d;
				all->spr[j].d = tmp;
				sw = all->spr[i].order;
				all->spr[i].order = all->spr[j].order;
				all->spr[j].order = sw;
			}
			j++;
		}
		i++;
	}
}

void	init_sprite(t_all *all)//sprite casting begin
{
	int	i;

	i = 0;
	while (i < all->rayc.spr_num)
	{
		all->spr[i].order = i;
		all->spr[i].d = ((all->rayc.pos_x - all->spr[i].x) * (all->rayc.pos_x - all->spr[i].x) + 
			(all->rayc.pos_y - all->spr[i].y) * (all->rayc.pos_y - all->spr[i].y));
		i++;
	}
	sort_spr(all);//sort sprites from far to close
	//after sorting the sprites, do the projection and draw them
	i = 0;
	while (i < all->rayc.spr_num)
	{
		//translate sprite position to relative to camera
		all->rays.x = all->spr[all->spr[i].order].x - all->rayc.pos_x;
		all->rays.y = all->spr[all->spr[i].order].y - all->rayc.pos_y;
		//transform sprite with the inverse camera matrix
		all->rays.inv_det = 1.0 / (all->rayc.plane_x * all->rayc.dir_y - all->rayc.dir_x * all->rayc.plane_y);//required for correct matrix multiplication
		all->rays.transform_x = all->rays.inv_det * (all->rayc.dir_y * all->rays.x - all->rayc.dir_x * all->rays.y);
		all->rays.transform_y = all->rays.inv_det * (-all->rayc.plane_y * all->rays.x + all->rayc.plane_x * all->rays.y);//this is actually the depth inside the screen, that what Z is in 3D
		all->rays.screen_x = (int)((all->map.width / 2) * (1 + all->rays.transform_x / all->rays.transform_y));
		//calculate height of the sprite on screen
		all->rays.h = abs((int)(all->map.height / all->rays.transform_y));//using 'transformY' instead of the real distance prevents fisheye
		draw_coords(all);
		//loop through every vertical stripe of the sprite on screen
		stripe_loop(all,i);
		i++;
	}
}

void	draw_coords(t_all *all)
{
	//calculate lowest and highest pixel to fill in current stripe
	all->rays.draw_start_y = -all->rays.h / 2 + all->map.height / 2;
	if (all->rays.draw_start_y < 0)
		all->rays.draw_start_y = 0;
	all->rays.draw_end_y = all->rays.h / 2 + all->map.height / 2;
	if (all->rays.draw_end_y >= all->map.height)
		all->rays.draw_end_y = all->map.height - 1;
	//printf("%d\n", all->map.height);
	//calculate width of the sprite
	all->rays.w = abs((int)(all->map.height / all->rays.transform_y));
	all->rays.draw_start_x = -all->rays.w / 2 + all->rays.screen_x;
	if (all->rays.draw_start_x < 0)
		all->rays.draw_start_x = 0;
	all->rays.draw_end_x = all->rays.w / 2 + all->rays.screen_x;
	if (all->rays.draw_end_x >= all->map.width)
		all->rays.draw_end_x = all->map.width - 1;
}

void	stripe_loop(t_all *all, int i)
{
	int	stripe;
	
	stripe = all->rays.draw_start_x;
	while (stripe < all->rays.draw_end_x && stripe < all->map.width)
	{
		all->rays.tex_x = (int)(256 * (stripe - (-all->rays.w / 2 + all->rays.screen_x)) * 
            all->spr[i].w / all->rays.w) / 256;
		/*
		the conditions in the if are:
    	1) it's in front of camera plane so you don't see things behind you
    	2) it's on the screen (left)
    	3) it's on the screen (right)
    	4) ZBuffer, with perpendicular distance
		*/
		if (all->rays.transform_y > 0 && stripe > 0 && 
			stripe < all->map.width && all->rays.transform_y < all->rays.dist_wall[stripe])
		    draw_spr(all, stripe, i);
        stripe++;
	}
}

void	draw_spr(t_all *all, int stripe, int i)
{
	int	d;
	int	y;

	y = all->rays.draw_start_y;
	while (y < all->rays.draw_end_y)//for every pixel of the current stripe
	{
		d = (int)((y * 256) - (all->map.height * 128) + (all->rays.h * 128));//256 and 128 factors to avoid floats
		all->rays.tex_y = ((d * all->spr[i].h) / all->rays.h) / 256;
		if (all->rays.tex_y > -1)
		{
			if (all->spr[i].addr[(all->spr[i].w * all->rays.tex_y) + all->rays.tex_x] != 0)
				all->spr[i].color = all->spr[i].addr[all->spr[i].w * all->rays.tex_y + all->rays.tex_x];//get current color from the texture
			else
				all->spr[i].color = 0x00FFFFFF;
		}
		if (all->spr[i].color != 0x00FFFFFF && all->rays.transform_y < all->rays.dist_wall[stripe])
				all->mlx.addr[all->map.width * y + stripe] = all->spr[i].color;
		y++;
	}
}