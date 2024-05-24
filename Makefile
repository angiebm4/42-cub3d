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
CFLAGS =	-Wall -Werror -Wextra -Imlx
#####################################################
LIB =	libft/libft.a
MLX =	mlx/libmlx.a
#####################################################

HEADERS_FOLDER =	include/
HEADERS_NAME =		cub3d.h
HEADERS=$(HEADERS_NAME:%.h=$(HEADERS_FOLDER)%.h)

VPATH = src:src/parser

SRC =		main.c

PARSER =	init_map.c

OBJ_DIR = obj/
OBJ =	$(SRC:%.c=$(OBJ_DIR)%.o) \
		$(PARSER:%.c=$(OBJ_DIR)%.o)

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
	@$(CC) $(CFLAGS) -c $< -o $@

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

r: run
run: all
	@./$(NAME) def_map.cub

v: valgrind
valgrind: all
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) def_map.cub
