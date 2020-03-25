SRCS		= cub3d.c events.c cub3d_misc.c raycasting.c movement.c map.c crosshair.c acceleration.c minimap.c ./get_next_line/get_next_line.c
OBJS		= ${SRCS:.c=.o}
NAME		= cub3d
CC			= cc
RM			= rm -f
CFLAGS		= #-Wall -Werror -Wextra
FRAMEWORK	= -L . -lmlx -lft -framework OpenGL -framework AppKit

.c.o:
			${CC} ${CFLAGS} -g -c $< -o ${<:.c=.o}

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
