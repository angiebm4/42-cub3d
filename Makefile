#####################################################
RED		=	\033[91;1m
GREEN	=	\033[92;1m
YELLOW	=	\033[93;1m
BLUE	=	\033[94;1m
PINK	=	\033[95;1m
CLEAR	=	\033[0m
#####################################################
NAME =		cub3D
CC = 		gcc
CFLAGS =	-Wall -Werror -Wextra -Imlx -g3
DEBUG_MODE	= -DDEBUG=0
#####################################################
LIB =	libft/libft.a
MLX =	mlx/libmlx.a
#####################################################

HEADERS_FOLDER =	include/
HEADERS_NAME =		cub3d.h
HEADERS=$(HEADERS_NAME:%.h=$(HEADERS_FOLDER)%.h)

VPATH = src:src/parser:src/utils:src/raycaster:src/moves:src/mouse

SRC =		main.c

PARSER =	parse.c				\
			parse_print.c		\
			parse_file.c		\
			save_placeholders.c	\
			save_map.c			\
			check_extension.c	\
			check_map.c			\
			flood_fill.c		\
			check_graphic.c		\
			clean_map.c

GRAFIC =	mlx_init.c	\
			mini_map.c	\
			hooks.c		\
			init_player.c
			
			
RENDER =	render.c			\
			raycasting_calcs.c	\
			raycasting_print.c

MOVES =		moves.c	\
			mouse_move.c	\
			rotate_player.c

MOUSE =		mouse_controller.c	\
			move_player.c	\
			mouse_display.c	\
			mouse_fix.c

UTILS =		line_utils.c	\
			map_utils.c		\
			pixel_utils.c

OBJ_DIR = obj/
OBJ =	$(SRC:%.c=$(OBJ_DIR)%.o) \
		$(PARSER:%.c=$(OBJ_DIR)%.o) \
		$(GRAFIC:%.c=$(OBJ_DIR)%.o)	\
		$(RENDER:%.c=$(OBJ_DIR)%.o)	\
		$(MOVES:%.c=$(OBJ_DIR)%.o)	\
		$(UTILS:%.c=$(OBJ_DIR)%.o)	\
		$(MOUSE:%.c=$(OBJ_DIR)%.o)

#####################################################

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(PINK)Compiling the librarys.$(CLEAR)"
	@$(MAKE) -sC ./libft
	@$(MAKE) -sC ./mlx
	@echo "$(GREEN)Librarys compiled correctly\n$(CLEAR)"
	@echo "$(PINK)Compiling 'cub3D'.$(CLEAR)"
	@$(CC) $(OBJ) $(LIB) $(MLX) -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -o $(NAME)
	@echo "$(GREEN)[OK]\n$(CLEAR)$(GREEN)Success!$(CLEAR)\n"

$(OBJ_DIR)%.o: %.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	@echo "$(BLUE)[ SRC ] Compiling $<$(CLEAR)"
	@$(CC) $(CFLAGS) $(DEBUG_MODE) -c $< -o $@

#####################################################

debug: DEBUG_MODE = -DDEBUG=1
debug: re

#####################################################

clean:
	@echo "$(PINK)Removing compiled files.$(CLEAR)"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) clean -sC ./libft
	@$(MAKE) clean -sC ./mlx
	@echo "$(GREEN)Object files removed correctly\n$(CLEAR)"

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) fclean -sC ./libft
	@echo "$(GREEN)Exec. files removed correctly\nSuccess!\n$(CLEAR)"


re: fclean all
.PHONY: clean fclean re all run

###############################################################################

# debug: re

###############################################################################

TRY_MAP=maps/small_map.cub

r: run
run: all
	@./$(NAME) $(TRY_MAP)

v: valgrind
valgrind: all
	@valgrind --track-origins=yes ./$(NAME) $(TRY_MAP)

raycaster:
	@gcc -Wall -Wextra -Werror -o raycaster raycaster.c -Lmlx/ -lmlx -lm -lX11 -lXext

.PHONY : raycaster