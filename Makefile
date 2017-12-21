NAME=ft_select
NAME_DBG=ft_selectdbg
NAME_SAN=ft_selectsan
SRC_NAME=main.c eval.c signal.c
SRC=$(addprefix src/, $(SRC_NAME))
OBJ=$(patsubst src/%.c, obj/%.o, $(SRC))
OBJ_DBG=$(patsubst src/%.c, obj_dbg/%.o, $(SRC))
OBJ_SAN=$(patsubst src/%.c, obj_san/%.o, $(SRC))
CC=clang
LIBS=-Llibft/ -lft -ltermcap
LIBS_DBG=-Llibft/ -lftdbg -ltermcap
LIBS_SAN=-Llibft/ -lftsan -ltermcap
CFLAGS=-Wall -Werror -Wextra -Iinclude -Ilibft/include
OPTI=-O3
SANFLAGS=-fsanitize=address -g

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft/ all
	$(CC) $(CFLAGS) $(OPTI) -o $(NAME) $(OBJ) $(LIBS)

$(NAME_DBG): $(OBJ_DBG)
	@make -C libft/ debug
	$(CC) $(CFLAGS) -g -o $(NAME_DBG) $(OBJ_DBG) $(LIBS_DBG)

$(NAME_SAN): $(OBJ_SAN)
	@make SANFLAGS="$(SANFLAGS)" -C libft/ san
	$(CC) $(CFLAGS) $(SANFLAGS) -o $(NAME_SAN) $(OBJ_SAN) $(LIBS_SAN)

obj/%.o: src/%.c
	@mkdir -p `dirname $@`
	$(CC) $(CFLAGS) $(OPTI) -c -o $@ $<

obj_dbg/%.o: src/%.c
	@mkdir -p `dirname $@`
	$(CC) $(CFLAGS) -g -c -o $@ $<

obj_san/%.o: src/%.c
	@mkdir -p `dirname $@`
	$(CC) $(CFLAGS) $(SANFLAGS) -c -o $@ $<

debug: $(NAME_DBG)
	@lldb $(NAME_DBG)

leaks: $(NAME_DBG)
	@MallocStackLogging=1 MallocStackLoggingNoCompact=1 MallocScribble=1 $(NAME_DBG)

san: $(NAME_SAN)

norme: $(SRC)
	@norminette $(SRC)
	@norminette include/ft_ls.h

clean:
	@make -C libft/ clean
	@rm -rf obj
	@rm -rf obj_dbg
	@rm -rf obj_san

fclean: clean
	@make -C libft/ fclean
	@rm -f $(NAME)
	@rm -f $(NAME_DBG)
	@rm -rf $(NAME_DBG).dSYM
	@rm -rf $(NAME_SAN)

re: fclean all
