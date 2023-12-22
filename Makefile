NAME = minishell

LIBFT_PATH = ./libft/
LIBFT = $(LIBFT_PATH)libft.a

INCLUDES = -I ./includes/

CFLAGS = -Wall -Werror -Wextra -g
OTHER_FLAGS = -L$(LIBFT_PATH) -lft

SRCS = ./sources/echo.c	./sources/tokenizer.c\
		./sources/here_doc.c	./sources/utils.c\

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
		@cc $(CFLAGS) $(OBJS) $(OTHER_FLAGS) -o $(NAME) -lreadline
		echo project built

$(LIBFT):
		echo building project
		@make $(LIBFT_PATH)

%.o: %.c
		@cc $(CFLAGS) $(INCLUDES) $(OTHER_FLAGS) -c $< -o $@

clean:
		@rm $(OBJS)
		@make -sC $(LIBFT_PATH) clean
		@rm -rf readline.supp

fclean: clean
		@rm $(NAME)

readline.supp:
		wget https://raw.githubusercontent.com/benjaminbrassart/minishell/master/readline.supp

valgrind:$(NAME) readline.supp
		valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=readline.supp ./$(NAME)

re: fclean all