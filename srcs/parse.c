/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legunshi <legunshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 20:55:00 by legunshi          #+#    #+#             */
/*   Updated: 2021/03/21 21:06:54 by legunshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	parse_line(t_all *all, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	check_ident(all, line, i);
	if (line[i] == 'N' && line[i + 1] != 'O')
		close_prog(all, 38);
	if (line[i] == 'W' && line[i + 1] != 'E')
		close_prog(all, 38);
	if (line[i] == 'E' && line[i + 1] != 'A')
		close_prog(all, 38);
	if (line[i] == 'R' && line[i + 1] != ' ')
		close_prog(all, 38);
	if (line[i] == 'F' && line[i + 1] != ' ')
		close_prog(all, 38);
	if (line[i] == 'C' && line[i + 1] != ' ')
		close_prog(all, 38);
	if (line[i] == 'R' && line[i + 1] == ' ' && all->ident.r == 0)
		parse_resol(all, line, i);
	if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		parse_text(all, line, i);
	parse_color(all, line, i);
	parse_map(all, line);
}

void	plr_direction1(t_all *all)
{
	if (all->map.orientation == 'N')
	{
		all->rayc.dir_x = -1;
		all->rayc.dir_y = 0;
		all->rayc.plane_x = 0;
		all->rayc.plane_y = 0.66;
	}
	else if (all->map.orientation == 'S')
	{
		all->rayc.dir_x = 1;
		all->rayc.dir_y = 0;
		all->rayc.plane_x = 0;
		all->rayc.plane_y = -0.66;
	}
}

void	plr_direction2(t_all *all)
{
	if (all->map.orientation == 'W')
	{
		all->rayc.dir_x = 0;
		all->rayc.dir_y = -1;
		all->rayc.plane_x = -0.66;
		all->rayc.plane_y = 0;
	}
	else if (all->map.orientation == 'E')
	{
		all->rayc.dir_x = 0;
		all->rayc.dir_y = 1;
		all->rayc.plane_x = 0.66;
		all->rayc.plane_y = 0;
	}
}

void	line_check(t_all *all)
{
	if (all->ident.r == 0 || all->ident.no == 0 || all->ident.so == 0 ||
		all->ident.ea == 0 || all->ident.we == 0 || all->ident.s == 0 ||
		all->ident.f == 0 || all->ident.c == 0 || all->ident.map_rows == 0)
		close_prog(all, 20);
	if (all->ident.map_rows == 0)
		close_prog(all, 20);
	if (all->ident.map_rows - all->map.rows > 0)
		close_prog(all, 20);
}

int		parse_file(t_all *all, char *file)
{
	char	*line;
	int		fd;

	if ((fd = open(file, O_RDONLY)) < 1)
		close_prog(all, 5);
	while (get_next_line(fd, &line))
	{
		parse_line(all, line);
		free(line);
		line = NULL;
	}
	parse_line(all, line);
	free(line);
	line = NULL;
	close(fd);
	line_check(all);
	mapsaving(all);
	mapchecking(all);
	plr_direction1(all);
	plr_direction2(all);
	return (1);
}
