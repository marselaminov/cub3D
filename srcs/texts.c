#include "../includes/cub3d.h"

void	drawn_on_screen(t_all *all, int width, int height)
{
	t_text	*wall_text;
	
	all->rayc.lineheight = (int)(all->map.height / all->rayc.perp_walldist);//calculate height of line to draw on screen
	all->rayc.draw_start = all->map.height / 2 - all->rayc.lineheight / 2;//calculate lowest and highest pixel to fill in current stripe
	all->rayc.draw_end = all->map.height / 2 + all->rayc.lineheight / 2;
	if (all->rayc.draw_start < 0)
		all->rayc.draw_start = 0;
	if (all->rayc.draw_end >= all->map.height)
		all->rayc.draw_end = all->map.height - 1;
	if (all->rayc.side == 0 && all->rayc.raydir_x > 0)
		wall_text = &all->east;
	else if (all->rayc.side == 0 && all->rayc.raydir_x < 0)
		wall_text = &all->west;
	else if (all->rayc.side == 1 && all->rayc.raydir_y > 0)
		wall_text = &all->south;
	else
		wall_text = &all->north;
	draw_text(all, width, wall_text);
	height = all->rayc.draw_end;
	while (height < all->map.height)
	{
		all->mlx.addr[((height * all->mlx.line_length) + (width * 4)) / 4] =
			all->map.floor;
		all->mlx.addr[width + (all->map.height - height - 1) * 
			all->map.width] = all->map.ceiling;
		height++;
	}
}

void	draw_text(t_all *all, int width, t_text *wall_text)
{
	double	wall_x;//where exactly the wall was hit
	/*The value wallX represents the exact(точное) value where the wall was hit, not just the integer coordinates 
	of the wall. This is required(требуется) to know which x-coordinate of the texture we have to use*/
	int		text_width;//the x-coordinate of the texture
	int		text_height;//the y-coordinate of the texture
	int		height;
	double	step;
	
	if (all->rayc.side == 0)
		wall_x = all->rayc.pos_y + all->rayc.perp_walldist * all->rayc.raydir_y;
	else
		wall_x = all->rayc.pos_x + all->rayc.perp_walldist * all->rayc.raydir_x;
	wall_x -= floor(wall_x);
	text_width = wall_x * (double)wall_text->w;//x coordinate on the texture
	height = all->rayc.draw_start;
	while (height < all->rayc.draw_end)//for every pixel of the current stripe
	{
		step = 1.0 * wall_text->h / all->rayc.lineheight;//how much to increase the texture coordinate per screen pixel
		text_height = (height - all->map.height / 2 + all->rayc.lineheight / 2) * step;//starting texture coordinate
		if (text_height < 0)//checking height of texture
			close_prog(all, 25);
		all->mlx.addr[all->map.width * height + width] = wall_text->addr[wall_text->w * text_height + text_width];
		height++;
	}
}

t_text		get_text(char *txt, t_all *all)
{
	t_text	text;

	if (!(text.img = mlx_xpm_file_to_image(all->mlx.mlx, txt, &text.w, &text.h)))
		close_prog(all, 25);
	if (!(text.addr = (int *)mlx_get_data_addr(text.img, &text.bits_per_pixel,
		&text.line_length, &text.endian)))
		close_prog(all, 25);
	return (text);
}

void		launch_wall_text(t_all *all)
{
	all->north = get_text(all->map.north, all);
	all->south = get_text(all->map.south, all);
	all->east = get_text(all->map.east, all);
	all->west = get_text(all->map.west, all);
}

void		launch_spr_text(t_all *all)
{
	int		spr;

	if (!(all->spr = (t_sprite *)ft_calloc(sizeof(t_sprite), all->rayc.spr_num)))
		close_prog(all, 6);
	spr = 0;
	while (spr < all->rayc.spr_num)
	{
		if (!(all->spr[spr].img = mlx_xpm_file_to_image(all->mlx.mlx, all->map.sprite, 
			&all->spr[spr].w, &all->spr[spr].h)))
			close_prog(all, 24);
		if (!(all->spr[spr].addr = (int *)mlx_get_data_addr(all->spr[spr].img,
			&all->spr[spr].bits_per_pixel, &all->spr[spr].size_line, &all->spr[spr].endian)))
			close_prog(all, 24);
		spr++;
	}
}