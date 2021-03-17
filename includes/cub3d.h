#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

# define W 13
# define S 1
# define D 2
# define A 0
# define R 123
# define L 124
# define E 53

# define BUFFER_SIZE 1000

t_list			*g_rubbish;

typedef struct		s_ident
{
	int				r;
	int				no;
	int				so;
	int				ea;
	int				we;
	int				s;
	int				f;
	int				c;
	int				map_rows;
	int				plr;
}					t_ident;

typedef struct		s_text
{
	void			*img;
	int				*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				w;
	int				h;
}					t_text;

typedef struct		s_colors
{
	int				ceiling;
	int				floor;
	int				north;
	int				south;
	int				east;
	int				west;
	int				wall;
}					t_colors;

typedef struct		s_move
{
	double			olddir_x;
	double			oldplane_x;
	double			rot_speed;
	double			move_speed;
	int				up;
	int				down;
	int				right;
	int				left;
	int				rot_right;
	int				rot_left;
}					t_move;

typedef struct		s_raycast
{
	double			pos_x;//start pos plr
	double			pos_y;
	double			dir_x;//plr direction
	double			dir_y;
	double			plane_x;//plr camera plane
	double			plane_y;
	double			camera_x;//x-coordinate on the camera plane
	double			raydir_x;//ray position and direction
	double			raydir_y;
	double			deltdist_x;//length of ray from one x or y-side to next x or y-side
	double			deltdist_y;
	double			sidedist_x;//length of ray from current position to next x or y-side
	double			sidedist_y; 
	double			perp_walldist;//the length of the ray in the future (maybe)
	int				map_x;//current square of the map the ray is in (which box of the map we're in)
	int				map_y;
	int				step_x;//what direction to step in x or y-direction (either +1 or -1)
	int				step_y;
	int				side;//was a NS or a EW wall hit?
	int				hit;//was there a wall hit?
	int				lineheight;//height of the vertical line that should be drawn
	int				draw_start;
	int				draw_end;
	int				spr_num;
}					t_raycast;

typedef struct		s_rayspr
{
	double			x;
	double			y;
	double			inv_det;
	double			transform_x;
	double			transform_y;
	double			*dist_wall;
	int				screen_x;
	int				draw_start_x;
	int				draw_end_x;
	int				draw_start_y;
	int				draw_end_y;
	int				tex_x;
	int				tex_y;
	int				h;
	int				w;
}					t_rayspr;

typedef struct		s_sprite
{
	double			d;
	double			x;
	double			y;
	void			*img;
	int				*addr;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	int				w;
	int				h;
	int				color;
	int				order;
}					t_sprite;

typedef struct		s_map
{
	char			orientation;
	char			**map;
	char			*tmp;
	char			*north;
	char			*south;
	char			*east;
	char			*west;
	char			*sprite;
	int				rows;
	int				col;
	int				width;
	int				height;
	int				floor;
	int				ceiling;
}					t_map;

typedef struct		s_mlx
{
	void			*mlx;
	void			*mlx_win;
	void			*img;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				*addr;
}					t_mlx;

typedef struct		s_bmp
{
	unsigned char	allheader[54];
	unsigned char	rgb[3];
	int				pad_size;
}					t_bmp;

typedef struct		s_all
{
	t_map			map;
	t_raycast       rayc;
	t_rayspr		rays;
	t_move          move;
	t_colors		color;
	t_text		    north;
	t_text		    south;
	t_text		    east;
	t_text          west;
	t_ident         ident;
	t_mlx			mlx;
	t_sprite		*spr;
	int				save;

}					t_all;

void    			create_frame(t_all *all);
int					close_prog(t_all *all, int err);
int					cubcheck(char *s);
int     			savecheck(char *arg, char *save);
int					cub_atoi(char *line, int *i);
void    			get_err1(int err);
void    			get_err_2(int err);
void    			get_err_3(int err);
void				parse_color(t_all *all, char *line, int i);
char				*save_text(char *line, int i);
int					save_color(t_all *all, char *line, int i);
void				check_ident(t_all *all, char *line);
void        		parse_text(t_all *all, char *line, int i);
void        		parse_line(t_all *all, char *line);
int         		parse_file(t_all *all, char *file);
void        		parse_map(t_all *all, char *line);
void        		make_map(t_all *all, char *line);
void				mapsaving(t_all *all);
void				get_map_memory(t_all *all);
void				mapchecking(t_all *all);
void				player_pos(t_all *all, int s, int v);
void				we_ea_borders(t_all *all);
void				no_so_borders(t_all *all);
void				map_borders(t_all *all);
void				plr_direction(t_all *all);
void				start_prog(t_all *all);
void				launch_prog(t_all *all);
void				init_raycast(t_all *all);
void				step_x(t_all *all);
void				step_y(t_all *all);
void				dda_init(t_all *all);
void				len_of_the_ray(t_all *all);
void				drawn_on_screen(t_all *all, int width, int height);
int					keypress(int key, t_all *all);
int					keyrelease(int key, t_all *all);
int					keyexit(t_all *all);
void				move_r_l(t_all *all);
void				move_up_down(t_all *all);
void				rotate_right(t_all *all);
void				rotate_left(t_all *all);
int					move_plr(t_all *all);
void				launch_wall_text(t_all *all);
t_text				get_text(char *txt, t_all *all);
void				draw_text(t_all *all, int width, t_text *wall_text);
int					check_color(t_all *all, int r, int g, int b);
void				get_screen_size(t_all *all);
void				launch_spr_text(t_all *all);
void				spr_in_map(t_all *all);
void				init_sprite(t_all *all);
void				sort_spr(t_all *all);
void				draw_coords(t_all *all);
void				draw_spr(t_all *all, int stripe, int i);
void				stripe_loop(t_all *all, int i);
void				bitmap_main(t_all *all);
void				screen_win(t_all *all, int fd, t_bmp *bmp);
void				header(t_bmp *bmp, t_all *all, int allsize);
void				close_map(t_all *all);
void				close_spr(t_all *all);
void				map_char_check(t_all *all, int s, int v);

int     			get_next_line(int fd, char **line);
int     			ft_check_func(char **line, char **buff, int bytes);
size_t  			ft_strlen1(const char *str);
char				*ft_strjoin1(char const *s1, char const *s2);
char				*ft_strdup1(const char *s);
char				*ft_strchr1(const char *str, int c);

int		first_color(t_all *all, char *line, int i);

#endif