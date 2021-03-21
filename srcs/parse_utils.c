#include "../includes/cub3d.h"

void        make_map(t_all *all, char *line)
{
    if (!all->map.tmp)
        all->map.tmp = ft_strdup1("");
    else
        all->map.tmp = ft_strjoin1(all->map.tmp, "\n");
    all->map.tmp = ft_strjoin1(all->map.tmp, line);
    all->map.rows++;
}

void        parse_map(t_all *all, char *line)
{
    int     i;

    i = 0;
    while(line[i] == ' ')
        i++;
    if (line[i] == '1' || line[i] == '0')
    {
        if (all->ident.r == 1 && all->ident.no == 1 && 
            all->ident.so == 1 && all->ident.ea == 1 &&
            all->ident.we == 1 && all->ident.s == 1 &&
            all->ident.f == 1 && all->ident.c == 1)
        {
            make_map(all, line);
            all->ident.map_rows++;
        }
        else
            close_prog(all, 18);
    }
    else if (all->ident.map_rows)
        all->ident.map_rows++;
    // while(line[i] == ' ')
    //     i++;
    if (line[i] != '1' && line[i] != '0' && line[i] != 'R' && line[i] != 'N' && 
        line[i] != 'S' && line[i] != 'E' && line[i] != 'W' &&
        line[i] != 'F' && line[i] != 'C' && line[i] != '\0')
        close_prog(all, 19);
}

void        parse_text(t_all *all, char *line, int i)
{
    if (line[i] == 'N' && line[i + 1] == 'O' && all->ident.no == 0)
    {
        all->ident.no = 1;
        all->map.north = save_text(all, line, i);
    }
    else if (line[i] == 'S' && line[i + 1] == 'O' && all->ident.so == 0)
    {
        all->ident.so = 1;
        all->map.south = save_text(all, line, i);
    }
    else if (line[i] == 'W' && line[i + 1] == 'E' && all->ident.we == 0)
    {
        all->ident.we = 1;
        all->map.west = save_text(all, line, i);
    }
    else if (line[i] == 'E' && line[i + 1] == 'A' && all->ident.ea == 0)
    {
        all->ident.ea = 1;
        all->map.east = save_text(all, line, i);
    }
    else if (line[i] == 'S' && line[i + 1] == ' ' && all->ident.s == 0)
    {
        all->ident.s = 1;
        all->map.sprite = save_text(all, line, i);
    }
}

// void	parse_resol(t_all *all, char *line, int i)
// {
// 	all->ident.r = 1;
// 	i++;
// 	while (line[i] == ' ')
// 		i++;
// 	all->map.width = cub_atoi(line, &i);
// 	all->map.height = cub_atoi(line, &i);
// }

// void	parse_resol(t_all *all, char *line, int i)
// {
//     all->ident.r = 1;
// 	i++;
// 	while (line[i] == ' ')
// 		i++;
//     if (ft_isdigit(line[i]))
// 		all->map.width = ft_atoi(&line[i]);
// 	while (ft_isdigit(line[i]))
// 		i++;
// 	while (line[i] == ' ')
// 		i++;
// 	if (ft_isdigit(line[i]))
// 		all->map.height = ft_atoi(&line[i]);
//     // while (line[i] >= '0' && line[i] <= '9')
//     // {
//     //     all->map.width = ft_atoi(&line[i]);
//     //     i++;
//     // }
//     // while (line[i] == ' ')
// 	// 	i++;
//     // while (line[i] >= '0' && line[i] <= '9')
//     // {
//     //     all->map.height = ft_atoi(&line[i]);
//     //     i++;
//     // }
// }


void	parse_color(t_all *all, char *line, int i)
{
	if (line[i] == 'F' && line[i + 1] == ' ' && all->ident.f == 0)
    {
        all->ident.f = 1;
        all->map.floor = save_color(all, line, i);
    }
	else if (line[i] == 'C' && line[i + 1] == ' ' && all->ident.c == 0)
    {
        all->ident.c = 1;
        all->map.ceiling = save_color(all, line, i);
    }
}
