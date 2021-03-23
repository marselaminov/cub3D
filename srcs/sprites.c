/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legunshi <legunshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 20:11:26 by legunshi          #+#    #+#             */
/*   Updated: 2021/03/22 20:24:09 by legunshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	sort_spr(t_all *all)
{
	int	tmp;
	int	i;
	int	j;
	int	sw;

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

void	sprite_sorting(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->rayc.spr_num)
	{
		all->spr[i].order = i;
		all->spr[i].d = ((all->rayc.pos_x - all->spr[i].x) * (all->rayc.pos_x -
		all->spr[i].x) + (all->rayc.pos_y - all->spr[i].y) * (all->rayc.pos_y -
																all->spr[i].y));
		i++;
	}
	sort_spr(all);
}

void	draw_coords(t_all *all)
{
	all->rays.draw_start_y = -all->rays.h / 2 + all->map.height / 2;
	if (all->rays.draw_start_y < 0)
		all->rays.draw_start_y = 0;
	all->rays.draw_end_y = all->rays.h / 2 + all->map.height / 2;
	if (all->rays.draw_end_y >= all->map.height)
		all->rays.draw_end_y = all->map.height - 1;
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
		all->rays.tex_x = (int)(256 * (stripe - (-all->rays.w / 2 +
		all->rays.screen_x)) * all->spr[i].w / all->rays.w) / 256;
		if (all->rays.transform_y > 0 && stripe > 0 && stripe <
		all->map.width && all->rays.transform_y < all->rays.dist_wall[stripe])
			draw_spr(all, stripe, i);
		stripe++;
	}
}

void	draw_spr(t_all *all, int stripe, int i)
{
	int	d;
	int	y;

	y = all->rays.draw_start_y;
	while (y < all->rays.draw_end_y)
	{
		d = (int)((y * 256) - (all->map.height * 128) + (all->rays.h * 128));
		all->rays.tex_y = ((d * all->spr[i].h) / all->rays.h) / 256;
		if (all->rays.tex_y > -1)
		{
			if (all->spr[i].addr[(all->spr[i].w * all->rays.tex_y) +
				all->rays.tex_x] != 0)
				all->spr[i].color = all->spr[i].addr[all->spr[i].w *
				all->rays.tex_y + all->rays.tex_x];
			else
				all->spr[i].color = 0x00FFFFFF;
		}
		if (all->spr[i].color != 0x00FFFFFF && all->rays.transform_y <
			all->rays.dist_wall[stripe])
			all->mlx.addr[all->map.width * y + stripe] = all->spr[i].color;
		y++;
	}
}
