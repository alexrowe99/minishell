SRC = src/*.c


LIBFT = libft
INC = inc

LIBS = -L$(LIBFT) -lft -lreadline
HEADERS = -I$(INC) -I$(LIBFT)
FLAGS = -Wall -Werror -Wextra $(LIBS) $(HEADERS)

all:
	@make -s -C $(LIBFT)
	@echo Compiling libft
	@gcc $(SRC) $(FLAGS) -o minishell 
	@echo Good to go
	

clean:
	@clear
	@rm -f minishell
	@make fclean -s -C $(LIBFT)
	@echo nothing here anymore, well, except .c

fclean: clean

re: clean all
