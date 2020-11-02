SRCS		= cub3d.c events.c movement.c \
				./textures.c \
				./map/parser_color.c ./map/parser_file.c ./map/parser_map.c \
				./map/parser_resolution.c ./map/parser_texture.c \
				./map/parser_utils.c ./map/parser_vars.c \
				./render/screenshot.c \
				./raycasting/raycasting.c \
				./sprites/sprite_utils.c ./sprites/sprites.c \
				./map/parser_sprites.c \
				./utils/render_utils.c ./utils/misc.c \
				./get_next_line/get_next_line.c
OBJS		= ${SRCS:.c=.o}
NAME		= cub3D
CC			= cc
RM			= rm -f
CFLAGS		= -g3 -Wall -Werror -Wextra
FRAMEWORK	= -lz -L . -lmlx -lft -framework OpenGL -framework AppKit

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			${MAKE} -C ./minilibx
			${MAKE} -C ./libft
			mv ./minilibx/libmlx.a .
			mv ./libft/libft.a .
			${CC} -o ${NAME} ${OBJS} ${FRAMEWORK}

all:		${NAME}

clean:
			${RM} ${OBJS}
			${MAKE} clean -C ./minilibx
			${MAKE} clean -C ./libft

fclean : 	clean
			${RM} ${NAME} libmlx.a libft.a

re:			fclean all

.PHONY:		re all clean fclean
