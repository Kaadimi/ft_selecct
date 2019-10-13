NAME = ft_select

LIBSRC = libft/libft.a
LIBPATH = libft/

OBJ = main.o\
	  movements.o\
	  helping_functions.o\
	  print_part.o\
	  start_proc.o\
	  left_right.o\
	  choices_altr.o\
	  input_modes.o
	  
FLAG = -Wall -Werror -Wextra
TERM_LIB = -ltermcap

all: $(NAME)

$(NAME): $(LIBSRC) $(OBJ)
		gcc $(FLAG) $(OBJ) $(LIBSRC) $(TERM_LIB) -o $(NAME)

%.o : %.c
		gcc $(FLAG) -c $< -o $@
$(LIBSRC):
		make -C $(LIBPATH)

clean:
		make clean -C $(LIBPATH)
			/bin/rm -f $(OBJ)
fclean: clean
		make fclean -C $(LIBPATH)
			/bin/rm -f $(NAME)
re: fclean all
