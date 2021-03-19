#include "../includes/cub3d.h"

int	keyexit(t_all *all)
{
	close_prog(all, 0);
	return (0);
}

int	keyrelease(int key, t_all *all)
{
	if (key == W)
		all->move.up = 0;
	if (key == S)
		all->move.down = 0;
	if (key == D)
		all->move.right = 0;
	if (key == A)
		all->move.left = 0;
	if (key == R)
		all->move.rot_right = 0;
	if (key == L) //
		all->move.rot_left = 0;
	if (key == E) //
		keyexit(all);
	return (0);
}

int	keypress(int key, t_all *all)
{
	if (key == W)
		all->move.up = 1;
	if (key == S)
		all->move.down = 1;
	if (key == D)
		all->move.right = 1;
	if (key == A)
		all->move.left = 1;
	if (key == R)
		all->move.rot_right = 1;
	if (key == L)
		all->move.rot_left = 1;
	return (0);
}