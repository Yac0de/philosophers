NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror

INCLUDES = -I./inc

SRC_DIR = src
OBJ_DIR = obj

SRC_FILES = main utils check_args init actions threads_routine threads_death ft_str display
SRC = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC_FILES)))

RED = \033[0;31m
GREEN = \033[0;32m
NO_COLOR = \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(GREEN)Compiling $(NAME)...$(NO_COLOR)"
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) -lpthread

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(GREEN)Compiled: $<$(NO_COLOR)"

clean:
	@echo "$(RED)Cleaning objects...$(NO_COLOR)"
	@rm -f $(OBJ)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(RED)Full cleaning...$(NO_COLOR)"
	@rm -f $(NAME)

re: fclean all
	@echo "$(GREEN)Recompiled$(NO_COLOR)"

.PHONY: all clean fclean re bonus
