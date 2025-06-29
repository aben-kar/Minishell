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
	$(EXECUTION_DIR)/built-in.c \
	$(EXECUTION_DIR)/execute_commande.c \
	$(EXECUTION_DIR)/external_command.c \
	$(EXECUTION_DIR)/external_utils.c \
	$(EXECUTION_DIR)/ft_cd_utils.c \
	$(EXECUTION_DIR)/ft_cd.c \
	$(EXECUTION_DIR)/ft_copier_env_utils.c \
	$(EXECUTION_DIR)/ft_copier_env.c \
	$(EXECUTION_DIR)/ft_echo.c \
	$(EXECUTION_DIR)/ft_env.c \
	$(EXECUTION_DIR)/ft_exit.c \
	$(EXECUTION_DIR)/ft_export_help.c \
	$(EXECUTION_DIR)/ft_export_utils.c \
	$(EXECUTION_DIR)/ft_export.c \
	$(EXECUTION_DIR)/ft_helper_pipe.c \
	$(EXECUTION_DIR)/ft_pipeline.c \
	$(EXECUTION_DIR)/ft_print_export.c \
	$(EXECUTION_DIR)/ft_pwd.c \
	$(EXECUTION_DIR)/ft_unset.c \
	$(EXECUTION_DIR)/ft_utils_pipeline.c \
	$(EXECUTION_DIR)/redirection_utils.c \
	$(EXECUTION_DIR)/redirection.c \
	$(EXECUTION_DIR)/utils.c \
	$(HELPER_DIR)/ft_calloc_gc.c \
	$(HELPER_DIR)/ft_itoa_gc.c \
	$(HELPER_DIR)/ft_split_gc.c \
	$(HELPER_DIR)/ft_strdup_gc.c \
	$(HELPER_DIR)/ft_strjoin_char_gc.c \
	$(HELPER_DIR)/ft_strjoin_gc.c \
	$(HELPER_DIR)/ft_strndup.c \
	$(HELPER_DIR)/ft_substr_gc.c \
	$(PARSER_DIR)/error.c \
	$(PARSER_DIR)/expander_utils.c \
	$(PARSER_DIR)/expander_utils2.c \
	$(PARSER_DIR)/expander.c \
	$(PARSER_DIR)/gc.c \
	$(PARSER_DIR)/helper_func.c \
	$(PARSER_DIR)/herdoc_utils.c \
	$(PARSER_DIR)/heredoc.c \
	$(PARSER_DIR)/parse_utils.c \
	$(PARSER_DIR)/signals.c \
	$(PARSER_DIR)/token_parser.c \
	$(PARSER_DIR)/token_utils.c \
	$(PARSER_DIR)/tokenizer.c

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
