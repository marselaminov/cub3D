#include "../includes/cub3d.h"

char	*save_text(char *line, int i)
{
	char	*text;

	while ((line[i] >= 'a' && line[i] <= 'z') || 
		(line[i] >= 'A' && line[i] <= 'Z'))
		i++;
	while (line[i] == ' ')
		i++;
	text = ft_strdup1(&line[i]);
	return (text);
}

int		check_color(t_all *all, int r, int g, int b)
{
	int color;

	if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
		close_prog(all, 17);
	color = r * 256 * 256 + g * 256 + b;
	return (color);
}

// int		first_color(t_all *all, char *line, int i)
// {
// 	int	r;

// 	r = 0;
	
// 	return (r);
// }

int		save_color(t_all *all, char *line, int i)
{
	int	r;
	int	g;
	int	b;

	r = 0;
	g = 0;
	b = 0;
	i++;
	while (line[i] == ' ')
		i++;
	if (!(line[i] >= '0' && line[i] <= '9'))
		close_prog(all, 35);
	if (line[i] >= '0' && line[i] <= '9')
		r = cub_atoi(line, &i);
	i++;
	while (line[i] == ' ')
		i++;
	if (line[i] != ',') // 2 color
		close_prog(all, 16);
	if (line[i] == ',')
		i++;
	while (line[i] == ' ')
		i++;
	if (!(line[i] >= '0' && line[i] <= '9'))
		close_prog(all, 35);
	if (line[i] >= '0' && line[i] <= '9')
		g = cub_atoi(line, &i);
	i++;
	if (line[i] != ',') // 3 color
		close_prog(all, 16);
	if (line[i] == ',')
		i++;
	while (line[i] == ' ')
		i++;
	if (!(line[i] >= '0' && line[i] <= '9'))
		close_prog(all, 35);
	if (line[i] >= '0' && line[i] <= '9')
		b = cub_atoi(line, &i);
	i++;
	if (line[i] != '\0')
		close_prog(all, 35);
	return (check_color(all, r, g, b));
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