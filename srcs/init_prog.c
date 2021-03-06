/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legunshi <legunshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 19:17:33 by legunshi          #+#    #+#             */
/*   Updated: 2021/03/22 20:22:49 by legunshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_sprite(t_all *all)
{
	int	i;

	sprite_sorting(all);
	i = 0;
	while (i < all->rayc.spr_num)
	{
		all->rays.x = all->spr[all->spr[i].order].x - all->rayc.pos_x;
		all->rays.y = all->spr[all->spr[i].order].y - all->rayc.pos_y;
		all->rays.inv_det = 1.0 / (all->rayc.plane_x * all->rayc.dir_y -
		all->rayc.dir_x * all->rayc.plane_y);
		all->rays.transform_x = all->rays.inv_det * (all->rayc.dir_y *
		all->rays.x - all->rayc.dir_x * all->rays.y);
		all->rays.transform_y = all->rays.inv_det * (-all->rayc.plane_y *
		all->rays.x + all->rayc.plane_x * all->rays.y);
		all->rays.screen_x = (int)((all->map.width / 2) *
		(1 + all->rays.transform_x / all->rays.transform_y));
		all->rays.h = abs((int)(all->map.height / all->rays.transform_y));
		draw_coords(all);
		stripe_loop(all, i);
		i++;
	}
}

void	create_frame(t_all *all)
{
	if (!(all->mlx.img = mlx_new_image(all->mlx.mlx, all->map.width,
		all->map.height)))
		close_prog(all, 24);
	if (!(all->mlx.addr = (int *)mlx_get_data_addr(all->mlx.img,
		&all->mlx.bits_per_pixel, &all->mlx.line_length, &all->mlx.endian)))
		close_prog(all, 24);
	if (!(all->rays.dist_wall = ft_calloc(sizeof(double), all->map.width)))
		close_prog(all, 1);
}

void	launch_prog(t_all *all)
{
	create_frame(all);
	init_raycast(all);
	init_sprite(all);
	if (all->rays.dist_wall)
	{
		free(all->rays.dist_wall);
		all->rays.dist_wall = NULL;
	}
	if (all->save == 1)
		bitmap_main(all);
	mlx_put_image_to_window(all->mlx.mlx, all->mlx.mlx_win, all->mlx.img, 0, 0);
	mlx_do_sync(all->mlx.mlx);
	mlx_destroy_image(all->mlx.mlx, all->mlx.img);
}

void	start_prog(t_all *all)
{
	if (!(all->mlx.mlx = mlx_init()))
		close_prog(all, 24);
	get_screen_size(all);
	if (all->save == 0)
	{
		if (!(all->mlx.mlx_win = mlx_new_window(all->mlx.mlx, all->map.width,
			all->map.height, "cub3D")))
			close_prog(all, 24);
	}
	launch_wall_text(all);
	launch_spr_text(all);
	spr_in_map(all);
	launch_prog(all);
	mlx_hook(all->mlx.mlx_win, 2, 1, &keypress, all);
	mlx_hook(all->mlx.mlx_win, 3, 2, &keyrelease, all);
	mlx_hook(all->mlx.mlx_win, 17, 0, &keyexit, all);
	mlx_hook(all->mlx.mlx_win, 33, 0, &keyexit, all);
	mlx_loop_hook(all->mlx.mlx, &move_plr, all);
	mlx_loop(all->mlx.mlx);
}

int		main(int argc, char **argv)
{
	t_all	*all;

	g_rubbish = (t_list *)malloc(sizeof(t_list));
	if (!(all = (t_all *)malloc(sizeof(t_all))))
		close_prog(all, 1);
	ft_bzero(all, sizeof(t_all));
	if (argc < 2 || argc > 3)
		close_prog(all, 2);
	if (cubcheck(argv[1]) == 1)
		close_prog(all, 3);
	if (argc == 3)
	{
		if (savecheck(argv[2], "--save"))
			all->save = 1;
		else
			close_prog(all, 4);
	}
	parse_file(all, argv[1]);
	start_prog(all);
	return (0);
}
