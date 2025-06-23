NAME = minishell

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 # -fsanitize=address
LDFLAGS = -Llibft -lft -lreadline -lhistory -lncurses

# Directories
LIBFT_DIR = libft
PARSER_DIR = parser
EXECUTION_DIR = execution
HELPER_DIR = helper_gc

# Source files
SRC = main.c \
      $(wildcard $(PARSER_DIR)/*.c) \
      $(wildcard $(EXECUTION_DIR)/*.c) \
	  $(wildcard $(HELPER_DIR)/*.c)

OBJ = $(SRC:.c=.o)

# Headers (including current dir)
INCLUDES = -I. -I$(LIBFT_DIR) -I$(PARSER_DIR) -I$(EXECUTION_DIR) -I$(HELPER_DIR)

# Rules
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_DIR)/libft.a
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
