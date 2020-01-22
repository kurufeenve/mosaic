NAME = converter

HEADER = includes

OFILES = main.o converter.o file_io.o #analyzer.o

FLAG = -Wall -Wextra #-Werror

all: $(NAME)

$(NAME): $(OFILES)
	@ar rc $(NAME) $(OFILES)
	@ranlib $(NAME)

%.o : %.c
	@gcc $(FLAG) -c -o $@ $< -I $(HEADER)

clean:
	@rm -rf $(OFILES)

fclean: clean
	@rm -f $(NAME)

re: fclean all
