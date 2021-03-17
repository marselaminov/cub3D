#include "../includes/cub3d.h"

int		get_fd(t_bmp *bmp, t_all *all)
{
	int	fd;

	fd = open("screen.bmp", O_WRONLY | O_CREAT, 0777 | O_TRUNC | O_APPEND);
	if (fd < 0)
		close_prog(all, 26);
	bmp->pad_size = all->map.width % 4;
	return (fd);
}

void	header(t_bmp *bmp, t_all *all, int allsize)
{
	bmp->allheader[0] = 'B';
	bmp->allheader[1] = 'M';
	bmp->allheader[2] = (allsize);
	bmp->allheader[3] = (allsize >> 8);
	bmp->allheader[4] = (allsize >> 16);
	bmp->allheader[5] = (allsize >> 24);
	bmp->allheader[10] = 54;
	bmp->allheader[14] = 40;
	bmp->allheader[18] = (all->map.width);
	bmp->allheader[19] = (all->map.width >> 8);
	bmp->allheader[20] = (all->map.width >> 16);
	bmp->allheader[21] = (all->map.width >> 24);
	bmp->allheader[22] = (all->map.height);
	bmp->allheader[23] = (all->map.height >> 8);
	bmp->allheader[24] = (all->map.height >> 16);
	bmp->allheader[25] = (all->map.height >> 24);
	bmp->allheader[26] = 1;
	bmp->allheader[28] = 24;
}

void		bitmap_main(t_all *all)
{
	t_bmp	*bmp;
	int		fd;
	int		allsize;

	if (!(bmp = (t_bmp *)malloc(sizeof(t_bmp))))
		close_prog(all, 1);
	ft_bzero(bmp, sizeof(t_bmp));
	fd = get_fd(bmp, all);
	ft_bzero(bmp->allheader, 54);
	allsize = 54 + 3 * (all->map.width + bmp->pad_size) * all->map.height;
	header(bmp, all, allsize);
	write(fd, &bmp->allheader, 54);
	screen_win(all, fd, bmp);
	close(fd);
	free(bmp);
	ft_putstr_fd("bmp file done\n", 1);
	close_prog(all, 0);
}

void	screen_win(t_all *all, int fd, t_bmp *bmp)
{
	int		x;
	int		y;
	int		color;

	ft_bzero(bmp->rgb, 3);
	y = all->map.height - 1;
	while (y > -1)
	{
		x = 0;
		while (x < all->map.width)
		{
			color = all->mlx.addr[y * all->map.width + x];
			write(fd, &color, 3);
			x++;
		}
		if (bmp->pad_size >= 1)
			write(fd, &bmp->rgb, bmp->pad_size);
		y--;
	}
}