CC = cc
CFLAGS = -Wall -Wextra -Werror -lreadline

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MINI_SHELL_SRC = src/main.c src/basic_exec.c src/parsing/input_parsing.c 

MINI_SHELL_EXE = minishell

NAME = $(MINI_SHELL_EXE)

all: $(NAME)

$(MINI_SHELL_EXE): $(MINI_SHELL_SRC) $(LIBFT)
	$(CC) $(CFLAGS) -o $(MINI_SHELL_EXE) $(MINI_SHELL_SRC) $(LIBFT)

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