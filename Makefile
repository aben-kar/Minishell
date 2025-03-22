NAME = shell

CC = cc
CFLAGS = -Wall -Wextra -Werror

# Include libft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = shell.c shell_utils.c function_helper.c
OBJ = $(SRC:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)  # Compile libft

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIBFT_DIR) -lft

%.o: %.c shell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean  # Clean libft objects

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean  # Full clean libft

re: fclean all
