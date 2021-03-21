/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legunshi <legunshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 18:41:12 by legunshi          #+#    #+#             */
/*   Updated: 2021/03/21 18:46:36 by legunshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_err_2(int err)
{
	if (err == 13)
		ft_putstr_fd("Error\nceiling color is already defined\n", 1);
	else if (err == 14)
		ft_putstr_fd("Error\nincorrect resolution\n", 1);
	else if (err == 15)
		ft_putstr_fd("Error\ninvalid color character\n", 1);
	else if (err == 16)
		ft_putstr_fd("Error\nno comma between colors\n", 1);
	else if (err == 17)
		ft_putstr_fd("Error\ncolor value must be is 0-255\n", 1);
	else if (err == 18)
		ft_putstr_fd("Error\nnot identifiers before map\n", 1);
	else if (err == 19)
		ft_putstr_fd("Error\ninvalid line in file\n", 1);
	else if (err == 20)
		ft_putstr_fd("Error\ninvalid file\n", 1);
	else if (err == 21)
		ft_putstr_fd("Error\nplayer was defined earlier\n", 1);
	else if (err == 22)
		ft_putstr_fd("Error\nmap is not closed of a west side\n", 1);
	else if (err == 23)
		ft_putstr_fd("Error\nnot borders on the map\n", 1);
	else if (err == 24)
		ft_putstr_fd("Error\nproblem with the mlx library\n", 1);
}

void	get_err_1(int err)
{
	if (err == 1)
		ft_putstr_fd("Error\nmemory not allocated\n", 1);
	else if (err == 2)
		ft_putstr_fd("Error\nnumber of arguments incorrect\n", 1);
	else if (err == 3)
		ft_putstr_fd("Error\nthe file must end .cub\n", 1);
	else if (err == 4)
		ft_putstr_fd("Error\nthe second argument must be --save\n", 1);
	else if (err == 5)
		ft_putstr_fd("Error\nthis file doesn't open\n", 1);
	else if (err == 6)
		ft_putstr_fd("Error\nresolution already defined\n", 1);
	else if (err == 7)
		ft_putstr_fd("Error\nnorth texture already defined\n", 1);
	else if (err == 8)
		ft_putstr_fd("Error\nsouth texture already defined\n", 1);
	else if (err == 9)
		ft_putstr_fd("Error\neast textures already defined\n", 1);
	else if (err == 10)
		ft_putstr_fd("Error\nwest textures already defined\n", 1);
	else if (err == 11)
		ft_putstr_fd("Error\nsprite texture already defined\n", 1);
	else if (err == 12)
		ft_putstr_fd("Error\nfloor color is already defined\n", 1);
}

void	get_err_3(int err)
{
	if (err == 25)
		ft_putstr_fd("Error\nincorrect texture\n", 1);
	else if (err == 26)
		ft_putstr_fd("Error\nfd for bmp < 0\n", 1);
	else if (err == 27)
		ft_putstr_fd("Error\nmap is not closed of a east side\n", 1);
	else if (err == 28)
		ft_putstr_fd("Error\nmap is not closed of a north side\n", 1);
	else if (err == 29)
		ft_putstr_fd("Error\nmap is not closed of a south side\n", 1);
	else if (err == 30)
		ft_putstr_fd("Error\nmap is not closed of a south side\n", 1);
	else if (err == 31)
		ft_putstr_fd("Error\ninvalid digit char in map\n", 1);
	else if (err == 32)
		ft_putstr_fd("Error\ninvalid direct char in map\n", 1);
	else if (err == 33)
		ft_putstr_fd("Error\nmap without player\n", 1);
	else if (err == 34)
		ft_putstr_fd("Error\nwrong char in map\n", 1);
	else if (err == 35)
		ft_putstr_fd("Error\ninvalid color\n", 1);
	else if (err == 36)
		ft_putstr_fd("Error\nwrong color char\n", 1);
}

int		close_prog(t_all *all, int err)
{
	if (err >= 1 && err <= 12)
		get_err_1(err);
	if (err >= 13 && err <= 24)
		get_err_2(err);
	if (err >= 25 && err <= 36)
		get_err_3(err);
	if (err == 37)
		ft_putstr_fd("Error\nplayer not defined\n", 1);
	if (err == 38)
		ft_putstr_fd("Error\ninvalid identificators\n", 1);
	close_spr(all);
	close_map(all);
	free(all->mlx.mlx);
	free(all->mlx.mlx_win);
	free(all->north.img);
	free(all->south.img);
	free(all->east.img);
	free(all->west.img);
	free(all->map.north);
	free(all->map.south);
	free(all->map.east);
	free(all->map.west);
	free(all->map.sprite);
	exit(0);
	return (0);
}

void	check_ident(t_all *all, char *line, int i)
{
	if (line[i] == 'R' && all->ident.r == 1)
		close_prog(all, 6);
	else if (line[i] == 'N' && line[i + 1] == 'O' && all->ident.no == 1)
		close_prog(all, 7);
	else if (line[i] == 'S' && line[i + 1] == 'O' && all->ident.so == 1)
		close_prog(all, 8);
	else if (line[i] == 'E' && line[i + 1] == 'A' && all->ident.ea == 1)
		close_prog(all, 9);
	else if (line[i] == 'W' && line[i + 1] == 'E' && all->ident.we == 1)
		close_prog(all, 10);
	else if (line[i] == 'S' && line[i + 1] == ' ' && all->ident.s == 1)
		close_prog(all, 11);
	else if (line[i] == 'F' && line[i + 1] == ' ' && all->ident.f == 1)
		close_prog(all, 12);
	else if (line[i] == 'C' && line[i + 1] == ' ' && all->ident.c == 1)
		close_prog(all, 13);
}
