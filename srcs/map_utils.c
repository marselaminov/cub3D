#include "../includes/cub3d.h"

void	we_ea_borders(t_all *all)
{
	int	str;
	int	val;

	str = 0;
	while (str < all->map.rows)
	{
		val = 0;
		while (all->map.map[str][val] == ' ')
		 	val++;
		if (all->map.map[str][val] != '1')
			close_prog(all, 22); // west side not closed of vall - != '1'
		// if (all->map.map[str][0] != '1' && all->map.map[str][0] != ' ')
		//  	close_prog(all, 22);
		str++;
	}
	str = 0;
	val = 0;
	while (str < all->map.rows)
	{
		while (all->map.map[str][val] && all->map.map[str][val] != '\0')
			val++;
		val--;
		if (all->map.map[str][val] != '1' && all->map.map[str][val] != ' ')
			close_prog(all, 27); // east side not closed of vall - != '1'
		str++;
		val = 0;
	}
}

void	no_so_borders(t_all *all)
{
	//int	str;
	int	val;

	// north side not closed of vall - != '1'
	val = 0;
	while (all->map.map[0][val])
	{
		if (all->map.map[0][val] != '1' && all->map.map[0][val] != ' ')
			close_prog(all, 28);
		val++;
	}
	val = 0;
	while (all->map.map[1][val])
	{
		if (all->map.map[1][val] == 'N' || all->map.map[1][val] == 'S' ||
			all->map.map[1][val] == 'E' || all->map.map[1][val] == 'W' ||
			all->map.map[1][val] == '0' || all->map.map[1][val] == '2' /*|| all->map.map[1][val] == '1'*/)
		{
			if (all->map.map[0][val] != '1')
				close_prog(all, 28);
		}
		val++;
	}
	// south side not closed of vall - != '1'
	val = 0;
	while (val < all->map.col)
	{
		if (all->map.map[all->map.rows - 1][val] != '1' &&
			all->map.map[all->map.rows - 1][val] != ' ' &&
			all->map.map[all->map.rows - 1][val] != '\0')
			close_prog(all, 29); 
		val++;
	}
	val = 0;
	while (all->map.map[all->map.rows - 2][val])
	{
		if (all->map.map[all->map.rows - 2][val] == 'N' || all->map.map[all->map.rows - 2][val] == 'S' ||
			all->map.map[all->map.rows - 2][val] == 'E' || all->map.map[all->map.rows - 2][val] == 'W' ||
			all->map.map[all->map.rows - 2][val] == '0' || all->map.map[all->map.rows - 2][val] == '2' /*|| 
			all->map.map[all->map.rows - 2][val] == '1'*/)
		{
			if (all->map.map[all->map.rows - 1][val] != '1')
				close_prog(all, 29);
		}
		val++;
	}
}

void	player_pos(t_all *all, int s, int v)
{
	if ((all->map.map[s][v] >= 'A' && all->map.map[s][v] <= 'Z') && all->map.map[s][v] != 'N' && 
		all->map.map[s][v] != 'S' && all->map.map[s][v] != 'E' && all->map.map[s][v] != 'W')
		close_prog(all, 32);
	if (all->map.map[s][v] >= 'a' && all->map.map[s][v] <= 'z')
		close_prog(all, 32);
	if ((all->map.map[s][v] == 'N' || all->map.map[s][v] == 'S' ||
		all->map.map[s][v] == 'E' || all->map.map[s][v] == 'W') &&
		all->ident.plr == 0)
	{
		all->ident.plr = 1;
		all->rayc.pos_x = s + 0.5;
		all->rayc.pos_y = v + 0.5;
		all->map.orientation = all->map.map[s][v];
	}
	else if ((all->map.map[s][v] == 'N' || all->map.map[s][v] == 'S' ||
		all->map.map[s][v] == 'E' || all->map.map[s][v] == 'W') &&
		all->ident.plr == 1)
		close_prog(all, 21);
}

void	map_borders(t_all *all)
{
	int	str;
	int	val;

	str = 1;
	while (str < all->map.rows - 1)
	{
		val = 1;
		while (all->map.map[str][val])
		{
			if (all->map.map[str][val] == ' ' && 
				((all->map.map[str][val - 1] == '0' && val != 0) ||
				(all->map.map[str][val + 1] == '0' && val != all->map.col - 1) ||
				all->map.map[str - 1][val] == '0' || all->map.map[str + 1][val] == '0' /*||
				(all->map.map[str - 1][val - 1] == '0' && val != 0) || (all->map.map[str - 1][val + 1] == '0' && val != all->map.col - 1) ||
				(all->map.map[str + 1][val - 1] == '0'  && val != 0) || (all->map.map[str + 1][val + 1] == '0' && val != all->map.col - 1)*/))
				close_prog(all, 23);
			if ((all->map.map[str][val] == '0' || all->map.map[str][val] == '2' || all->map.map[str][val] == 'N'
				 || all->map.map[str][val] == 'S' || all->map.map[str][val] == 'E' || all->map.map[str][val] == 'W') && 
				((all->map.map[str][val - 1] == '\0' && val != 0) ||
				(all->map.map[str][val + 1] == '\0' && val != all->map.col - 1) ||
				all->map.map[str - 1][val] == '\0' || all->map.map[str + 1][val] == '\0' ||
				(all->map.map[str - 1][val - 1] == ' ' && val != 0) || (all->map.map[str - 1][val + 1] == ' ' && val != all->map.col - 1) ||
				(all->map.map[str + 1][val - 1] == ' '  && val != 0) || (all->map.map[str + 1][val + 1] == ' ' && val != all->map.col - 1)))
				close_prog(all, 23);
			if ((all->map.map[str][val] == '0' || all->map.map[str][val] == '2' || all->map.map[str][val] == 'N'
				 || all->map.map[str][val] == 'S' || all->map.map[str][val] == 'E' || all->map.map[str][val] == 'W') && 
				((all->map.map[str][val - 1] == ' ' && val != 0) ||
				(all->map.map[str][val + 1] == ' ' && val != all->map.col - 1) ||
				/*all->map.map[str - 1][val] == ' ' || all->map.map[str + 1][val] == ' ' ||*/
				(all->map.map[str - 1][val - 1] == ' ' && val != 0) || (all->map.map[str - 1][val + 1] == ' ' && val != all->map.col - 1) /*||
				(all->map.map[str + 1][val - 1] == ' '  && val != 0) || (all->map.map[str + 1][val + 1] == ' ' && val != all->map.col - 1))*/))
				close_prog(all, 23);
			if ((all->map.map[str][val] == 'N' || all->map.map[str][val] == 'S' || all->map.map[str][val] == 'E' || 
				all->map.map[str][val] == 'W') && ((all->map.map[str][val - 1] == ' ' && val != 0) ||
				(all->map.map[str][val + 1] == ' ' && val != all->map.col - 1) ||
				all->map.map[str - 1][val] == ' ' || all->map.map[str + 1][val] == ' '))
				close_prog(all, 23);
			// if (all->map.map[str][val] == ' ' && 
			// 	((all->map.map[str][val - 1] != '1' && val != 0) ||
			// 	(all->map.map[str][val + 1] != '1' && val != all->map.col - 1) ||
			// 	all->map.map[str - 1][val] != '1' || all->map.map[str + 1][val] != '1'))
			// 	close_prog(all, 23);
			// if ((all->map.map[str][val] == '0' || all->map.map[str][val] == '2' || all->map.map[str][val] == 'N'
			// 	 || all->map.map[str][val] == 'S' || all->map.map[str][val] == 'E' || all->map.map[str][val] == 'W') && 
			// 	((all->map.map[str][val - 1] == ' ' && val != 0) ||
			// 	(all->map.map[str][val + 1] == ' ' && val != all->map.col - 1) ||
			// 	all->map.map[str - 1][val] == ' ' || (all->map.map[str - 1][val + 1] == ' ' && val != all->map.col - 1) 
			// 	|| (all->map.map[str - 1][val - 1] == ' ' && val != 0) ||
			// 	all->map.map[str + 1][val] == ' ' || (all->map.map[str + 1][val - 1] == ' ' && val != 0) || 
			// 	(all->map.map[str + 1][val + 1] == ' ' && val != all->map.col - 1)))
			// 	close_prog(all, 23);
			// if ((all->map.map[str][val] == '0' || all->map.map[str][val] == '2' || all->map.map[str][val] == 'N'
			// 	 || all->map.map[str][val] == 'S' || all->map.map[str][val] == 'E' || all->map.map[str][val] == 'W') && 
			// 	((all->map.map[str][val - 1] == ' ') ||
			// 	(all->map.map[str][val + 1] == ' ') ||
			// 	(all->map.map[str - 1][val] == ' ') || (all->map.map[str - 1][val] == ' ')))
			// 	close_prog(all, 23);
			val++;
		}
		str++;
	}
}

// int  zero_check(char **table, int i, int j)
// {
// 	if (i <= 0 || j <= 0)
// 		return (0);
// 	if (j + 2 > (int)ft_strlen(table[i - 1]) || j + 2 >
// 		(int)ft_strlen(table[i + 1]))
// 		return (0);
// 	if (!(table[i - 1][j] == '0' || table[i - 1][j] == '2'
// 		|| table[i - 1][j] == '1' || table[i - 1][j] == OK
// 		|| table[i - 1][j] == 'W' || table[i - 1][j] == OK + 1
// 		|| table[i - 1][j] == 'S' || table[i - 1][j] == 'N'
// 		|| table[i - 1][j] == 'E'))
// 		return (0);
// 	return (1);
// }

// int  map_ok(int str, int val, t_all *all)
// {
// 	if (all->map.map[str][val] != '1' && all->map.map[str][val] != OK 
// 		&& all->map.map[str][val] != OK + 1)
// 	{
// 		if (zero_check(all->map.map, str, val) == 0)
// 			return (0);
// 		if (all->map.map[str][val] == '0')
// 			all->map.map[str][val] = OK;
// 		if (all->map.map[str][val] == '2')
// 			all->map.map[str][val] = OK + 1;
// 		if (!map_ok(str - 1, val, all) || !map_ok(str + 1, val, all)
// 			|| !map_ok(str, val - 1, all) || !map_ok(str, val + 1, all))
// 			return (0);
// 	}
//  	return (1);
//}

void	mapchecking(t_all *all)
{
	int	str;
	int	val;

	str = 0;
	val = 0;
	while (str < all->map.rows)
	{
		while (all->map.map[str][val])
		{
			if (all->map.map[str][val] != '1' && all->map.map[str][val] != '0' &&
			all->map.map[str][val] != '2' && all->map.map[str][val] != ' ' &&
			all->map.map[str][val] != 'N' && all->map.map[str][val] != 'S' &&
			all->map.map[str][val] != 'E' && all->map.map[str][val] != 'W')
				close_prog(all, 34);
			player_pos(all, str, val);
			// if (map_ok(str, val, all) == 0)
			// 	close_prog(all, 23);
			if (all->map.map[str][val] == '2')
				all->rayc.spr_num += 1;
			val++;
		}
		str++;
		val = 0;
	}
	//printf("%s\n", all->map.map[2]);
	if (all->ident.plr != 1)
		close_prog(all, 37);
	map_borders(all);
	we_ea_borders(all);
	no_so_borders(all);
}