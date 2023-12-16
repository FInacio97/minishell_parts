NAME = minishell

LIBFT_PATH = ./libft/
LIBFT = $(LIBFT_PATH)libft.a

INCLUDES = -I ./includes/

CFLAGS = -Wall -Werror -Wextra -g
OTHER_FLAGS = -L$(LIBFT_PATH) -lft

SRCS = ./sources/echo.c ./sources/tokenizer.c\

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

fclean: clean
		@rm $(NAME)

re: fclean all