EXEC		:= cub3D

CC			= cc
CFLAGS		= -g -Wextra -Wall -Werror

LIBFT		= src/inc/libft/libft.a
LIBFT_D		= src/inc/libft

SRC_DIR		= src
SRC			= $(shell find $(SRC_DIR) -type f -name "*.c" | sed 's|$(SRC_DIR)/||')

OBJ_DIR		= obj
OBJ			= $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

GREEN		:= \033[0;32m
NC			:= \033[0m

all: $(EXEC)

$(LIBFT):
	@cd src/inc/libft && make -s

$(EXEC): MLX42 $(LIBFT) $(OBJ)
	@echo "$(NC)LINKING : $(GREEN)CUB3D APP"
	@$(CC) $(CFLAGS) -o $(EXEC) $(OBJ) -LMLX42/build -lmlx42 -IMLX42/include -lglfw -Lsrc/inc/libft -lft
	@echo "$(NC)BUILD : $(GREEN)SUCCESSFUL"

MLX42:
	@if [ ! -d "MLX42" ]; then \
		echo "Cloning MLX42"; \
		git clone https://github.com/codam-coding-college/MLX42.git MLX42; \
	else \
		echo "MLX42 already cloned"; \
	fi
	@cd MLX42 && cmake -B build && cmake --build build -j4
	@echo "$(NC)CLONE & BUILD : SUCCESSFUL$(NC)"

mlx: MLX42

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(NC)Compiling $(GREEN)$<..."
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(NC)CLEANING : $(GREEN) $(OBJ_DIR)/*.o"
	@cd src/inc/libft && make clean -s
	@echo "$(NC)CLEANING : $(GREEN) $(LIBFT_D)/*.o"

fclean: clean
	@cd src/inc/libft && make fclean -s
	@echo "$(NC)CLEANING : $(GREEN) CUB3d"
	@rm -f $(EXEC)

re: fclean all

.PHONY: all clean fclean re

