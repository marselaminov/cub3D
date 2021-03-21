NAME = cub3D

SRCS = 		srcs/init_prog.c \
			srcs/bitmap.c \
			srcs/errors.c \
			srcs/key.c \
			srcs/map_utils1.c \
			srcs/map_utils2.c \
			srcs/move.c \
			srcs/parse_utils.c \
			srcs/parse.c \
			srcs/raycast.c \
			srcs/save_values.c \
			srcs/sprites.c \
			srcs/texts.c \
			srcs/utils.c \
			srcs/utils2.c \
			srcs/get_next_line.c \
			srcs/get_next_line_utils.c

OBJS = 		$(SRCS:.c=.o)

CC = 		clang

RM = 		rm -rf

CFLAGS = 	-Wall -Werror -Wextra -g

MLXFLAGS = 	-framework OpenGL -framework Appkit

all:		$(NAME)

%.o:%.c
			$(CC) $(CFLAGS) -c -I./libft/ -I./includes/ -g -I./mlx/ $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
			cd ./libft/ && make && make bonus
			cd ./mlx/ && make
			$(CC) $(CFLAGS) $(MLXFLAGS) -o $(NAME) -I./mlx/ $(OBJS) ./libft/libft.a ./mlx/libmlx.a

clean:		
			$(RM) $(OBJS)
			@make clean -C libft
			@make clean -C mlx

fclean:		clean
			$(RM) $(NAME) screen.bmp
			@make fclean -C libft

re:			fclean all

.PHONY:		all 
			clean 
			fclean 
			re