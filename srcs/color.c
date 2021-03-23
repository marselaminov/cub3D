/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legunshi <legunshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 19:59:07 by legunshi          #+#    #+#             */
/*   Updated: 2021/03/22 20:06:06 by legunshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		check_color_digit(t_all *all, int r, int g, int b)
{
	int color;

	if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
		close_prog(all, 17);
	color = r * 256 * 256 + g * 256 + b;
	return (color);
}

void	checkkk(t_all *all, int *dig)
{
	if ((*dig) == 0)
		close_prog(all, 36);
}

int		colors_if(t_all *all, char *line, int *i, int *dig)
{
	int	comma;

	comma = 0;
	while (line[*i])
	{
		if (line[*i] == ' ')
			(*i)++;
		else if (line[*i] == 'F' || line[*i] == 'C')
			(*i)++;
		else if (line[*i] >= '0' && line[*i] <= '9')
		{
			(*i)++;
			(*dig)++;
		}
		else if (line[*i] == ',')
		{
			checkkk(all, dig);
			(*dig) = 1;
			comma++;
			(*i)++;
		}
		else
			close_prog(all, 36);
	}
	return (comma);
}

void	check_color_char(t_all *all, char *line)
{
	int	i;
	int	dig;
	int	comma;

	i = 0;
	dig = 0;
	comma = 0;
	while (line[i])
	{
		comma = colors_if(all, line, &i, &dig);
	}
	if (comma != 2 || dig == 0)
		close_prog(all, 36);
}

int		save_color(char *line, int *i, int *count)
{
	int	save;

	while (line[*i] == ' ')
		(*i)++;
	if (line[*i] >= '0' && line[*i] <= '9')
	{
		save = cub_atoi(line, i);
		*count += 1;
	}
	while (line[*i] == ' ')
		(*i)++;
	if (line[*i] == ',')
		(*i)++;
	while (line[*i] == ' ')
		(*i)++;
	return (save);
}
