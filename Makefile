CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MINI_SHELL_SRC = src/main.c src/basic_exec.c src/parsing/input_parsing.c src/read_line_loop.c src/ft_split_plus.c \
                 src/ft_find_cmd_path.c src/ft_init_cmd.c src/garbage_collector.c src/env_variables.c \
				 src/ft_heredoc.c src/ft_error.c src/builtins/export.c src/builtins/pwd.c \
				 src/check.c src/builtins/echo.c src/parsing/token_refiner.c src/builtins/cd.c \

MINI_SHELL_EXE = minishell

NAME = $(MINI_SHELL_EXE)

all: $(NAME)

$(MINI_SHELL_EXE): $(MINI_SHELL_SRC) $(LIBFT)
	$(CC) $(CFLAGS) -o $(MINI_SHELL_EXE) $(MINI_SHELL_SRC) $(LIBFT) -lreadline

$(LIBFT): 
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f *.o
	$(MAKE) -C $(LIBFT_DIR) clean

fclean:
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean $(LIBFT) all

party:
	curl parrot.live

.PHONY: all clean fclean re party