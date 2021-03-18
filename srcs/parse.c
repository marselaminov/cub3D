#include "../includes/cub3d.h"

void        parse_resol(t_all *all, char *line, int i)
{
    if (line[i] == 'R' && line[i + 1] == ' ' && all->ident.r == 0)
    {
        all->ident.r = 1;
	    i++;
	    while (line[i] == ' ')
		    i++;
        if (line[i] >= '0' && line[i] <= '9')
		    all->map.width = cub_atoi(line, &i);
	    while (line[i] == ' ')
		    i++;
	    if (line[i] >= '0' && line[i] <= '9')
		    all->map.height = cub_atoi(line, &i);
        if (line[i] != '\0')
		    close_prog(all, 14);
    }
    if (all->map.width == 0 || all->map.height == 0)
        close_prog(all, 14);
}

void        parse_line(t_all *all, char *line)
{
    int     i;

    i = 0;
    while (line[i] == ' ')
        i++;
    check_ident(all, line);
    parse_resol(all, line, i);
    parse_text(all, line, i);
    parse_color(all, line, i);
    parse_map(all, line);
    if (line[i] != '1' && line[i] != '0' && line[i] != 'R' && line[i] != 'N' && 
        line[i] != 'S' && line[i] != 'E' && line[i] != 'W' &&
        line[i] != 'F' && line[i] != 'C' && line[i] != '\0')
        close_prog(all, 19);
}

void	plr_direction(t_all *all)
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
	else if (all->map.orientation == 'W')
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

int         parse_file(t_all *all, char *file)
{
    char    *line;
    int     fd;

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
    if (all->ident.r == 0 || all->ident.no == 0 || all->ident.so == 0 || 
        all->ident.ea == 0 || all->ident.we == 0 || all->ident.s == 0 ||
        all->ident.f == 0 || all->ident.c == 0 || all->ident.map_rows == 0)
        close_prog(all, 20);
    if (all->ident.map_rows == 0)
        close_prog(all, 20);
    if (all->ident.map_rows - all->map.rows > 0)
        close_prog(all, 20);
    mapsaving(all);
    mapchecking(all);
    plr_direction(all);
    return (1);
}