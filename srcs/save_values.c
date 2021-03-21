/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legunshi <legunshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 21:16:23 by legunshi          #+#    #+#             */
/*   Updated: 2021/03/21 21:30:14 by legunshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*save_text(t_all *all, char *line, int i)
{
	char	*text;
	
	if ((line[i] >= 'a' && line[i] <= 'z') || 
		(line[i] >= 'A' && line[i] <= 'Z'))
		i++;
	if ((line[i] >= 'a' && line[i] <= 'z') || 
		(line[i] >= 'A' && line[i] <= 'Z'))
		i++;
	if (line[i] != ' ')
		close_prog(all, 25);
	while (line[i] == ' ')
		i++;
	text = ft_strdup(&line[i]);
	return (text);
}

int		check_color_digit(t_all *all, int r, int g, int b)
{
	int color;

	if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
		close_prog(all, 17);
	color = r * 256 * 256 + g * 256 + b;
	return (color);
}

// void	check_color_char2(char *line, int i)
// {
// 	if (line[i] == ' ')
// 			i++;
// 		else if (line[i] == 'F' || line[i] == 'C')
// 			i++;
// }

// void	check_comma(t_all *all, int comma, int digit)
// {
// 	if (comma != 2 || digit == 0)
// 		close_prog(all, 36);
// }

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
		if (line[i] == ' ')
			i++;
		else if (line[i] == 'F' || line[i] == 'C')
			i++;
		else if (line[i] >= '0' && line[i] <= '9')
		{
			i++;
			dig++;
		}
		else if (line[i] == ',')
		{
			if (dig == 0)
				close_prog(all, 36);
			dig = 0;
			dig++;
			comma++;
			i++;
		}
		else
			close_prog(all, 36);
	}
	if (comma != 2 || dig == 0)
		close_prog(all, 36);
}

// void	space_between(char *line, int i)
// {
// 	while (line[i] == ' ')
// 		i++;
// 	if (line[i] == ',')
// 		i++;
// 	while (line[i] == ' ')
// 		i++;
// }

int		save_color(t_all *all, char *line, int i)
{
	int	r;
	int	g;
	int	b;
	int	count;

	r = 0;
	g = 0;
	b = 0;
	count = 0;
	check_color_char(all, line);
	i++;
	while (line[i] == ' ')
		i++;
	if (line[i] >= '0' && line[i] <= '9')
	{
		r = cub_atoi(line, &i);
		count += 1;
	}
	while (line[i] == ' ')
		i++;
	if (line[i] == ',')
		i++;
	while (line[i] == ' ')
		i++;
	if (line[i] >= '0' && line[i] <= '9')
	{
		g = cub_atoi(line, &i);
		count += 1;
	}
	while (line[i] == ' ')
		i++;
	if (line[i] == ',')
		i++;
	while (line[i] == ' ')
		i++;
	if (line[i] >= '0' && line[i] <= '9')
	{
		b = cub_atoi(line, &i);
		count += 1;
	}
	if (count != 3)
		close_prog(all, 35);	
	if (line[i] != '\0')
		close_prog(all, 35);
	return (check_color_digit(all, r, g, b));
}

void	get_map_memory(t_all *all)
{
	int	i;
	int	columns;

	i = 0;
	columns = 0;
	while (all->map.tmp[i])
	{
		if (all->map.tmp[i] == '\n')
		{
			if (all->map.col < columns)
				all->map.col = columns - 1;
			columns = 0;
		}
		i++;
		columns++;
	}
	if (!(all->map.map = malloc(sizeof(char*) * (all->map.rows + 1))))
		close_prog(all, 1);
	i = 0;
	while (i < all->map.rows)
	{
		if (!(all->map.map[i] = ft_calloc(sizeof(char), (all->map.col + 1))))
		// if (!(all->map.map = malloc(sizeof(char*) * (all->map.col + 1))))
			close_prog(all, 1);
		i++;
	}
}

void	mapsaving(t_all *all)
{
	int	a;
	int	b;
	int	c;

	get_map_memory(all);
	a = 0;
	b = 0;
	c = 0;
	while (all->map.tmp[c])
	{
		if (all->map.tmp[c] != '\n')
		{
			all->map.map[a][b] = all->map.tmp[c];
			b++;
		}
		else
		{
			all->map.map[a][b] = '\0';
			a++;
			b = 0;
		}
		c++;
	}
	all->map.map[all->map.rows] = NULL;
}