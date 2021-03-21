/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legunshi <legunshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 18:39:52 by legunshi          #+#    #+#             */
/*   Updated: 2021/03/21 19:57:59 by legunshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	close_spr(t_all *all)
{
	int	i;

	i = 0;
	if (all->spr != 0)
	{
		while (i < all->rayc.spr_num)
		{
			if (all->spr[i].addr)
				mlx_destroy_image(all->mlx.mlx, all->spr[i].img);
			if (all->mlx.mlx && all->mlx.mlx_win)
				mlx_clear_window(all->mlx.mlx, all->mlx.mlx_win);
			i++;
		}
	}
	if (all->spr != 0)
		free(all->spr);
}

void	close_map(t_all *all)
{
	int	i;

	i = 0;
	if (all->map.tmp != 0)
		free(all->map.tmp);
	if (all->map.map)
	{
		while (i <= all->map.rows)
		{
			free(all->map.map[i]);
			i++;
		}
	}
	free(all->map.map);
}