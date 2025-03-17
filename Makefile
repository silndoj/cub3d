EXEC := cub3D

CC					=		cc
CFLAGS				=   -g -Wextra -Wall -Werror 

SRC_DIR		= 	src
SRC 		= 	$(wildcard $(SRC_DIR)/*.c)

OBJ_DIR		=	inv/obj
OBJ			= 	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))


GREEN := \033[0;32m
NC := \033[0m

all: $(EXEC)

$(EXEC):MLX42 $(OBJ)
				@echo "Linking $(EXEC)..."
				@$(CC) $(CFLAGS) -o $(EXEC) $(OBJ) -L./inv/MLX42/build/ -lmlx42 -Iinclude -lglfw
				@echo -e "$(GREEN)Build successful!$(NC)"

MLX42:
	@if [ ! -d "inv/MLX42" ]; then \
		echo "Cloning MLX42"; \
		git clone https://github.com/codam-coding-college/MLX42.git inv/MLX42; \
		else \
		echo "MLX42 already cloned"; \
		fi
	@cd inv/MLX42 && cmake -B build && cmake --build build -j4
	@echo -e "$(GREEN)Clone and Build successful!$(NC)"


mlx:		MLX42


$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning up object files..."
	rm -rf $(OBJ_DIR)

fclean: clean
	@echo "Cleaning up $(EXEC)..."
	rm -f $(EXEC)
	rm -rf inv

re: fclean all

.PHONY: all clean fclean re
