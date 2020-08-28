SRCS		= cub3d.c events.c camera.c movement.c \
				./map/parser.c ./map/spawn_parser.c \
				./utils/fps_counter.c ./utils/render_utils.c ./utils/misc.c \
				./get_next_line/get_next_line.c
OBJS		= ${SRCS:.c=.o}
NAME		= cub3d
CC			= cc
RM			= rm -f
CFLAGS		= #-Wall -Werror -Wextra
FRAMEWORK	= -lz -L . -lmlx -lft -framework OpenGL -framework AppKit

.c.o:
			${CC} ${CFLAGS} -g -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			${MAKE} -C ./minilibx
			${MAKE} -C ./libft
			mv ./minilibx/libmlx.a .
			mv ./libft/libft.a .
			${CC} -fsanitize=address -g -o ${NAME} ${OBJS} ${FRAMEWORK}

all:		${NAME}

clean:
			${RM} ${OBJS}
			${MAKE} clean -C ./minilibx
			${MAKE} clean -C ./libft

fclean : 	clean
			${RM} ${NAME} libmlx.a libft.a

re:			fclean all

.PHONY:		re all clean fclean
