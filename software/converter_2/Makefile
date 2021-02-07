
SRC 	=	converter.c\
			arg_parser.c\
			file_io.c\
			garbage_collector.c\
			processing.c\
            color_processing.c\
            tile_processing.c
 
INC		=	converter.h\
			common.h\
			arg_parser.h\
			file_io.h\
			garbage_collector.h\
			processing.h\
            color_processing.h\
            tile_processing.h

SRC_DIR	=	  ./src/
OBJ_DIR	=	  ./obj/
INC_DIR	=	  ./header/
NAME	=	  converter
CFLAG	=	  -Werror -Wextra -Wall -O0 -g
LIB     =	  -L./libft/ -lft libft/libft.a -lm
CC      =	  gcc

SRCS	=	  $(addprefix $(SRC_DIR),$(SRC))
OBJ		=	  $(SRC:.c=.o)
OBJS	=	  $(addprefix $(OBJ_DIR),$(OBJ))

#colours
NONE	=	  \033[0m
RED		=	  \033[31m
GREEN	=	  \033[32m
YELLOW	=	  \033[33m
BLUE	=	  \033[34m
MAGENTA	=	  \033[35m
CYAN	=	  \033[36m
#colours

.PHONY: all clean fclean re Lib objectdir

all: objectdir Lib $(NAME)

Lib:
		@make -C ./libft/
		@printf "\nLibft: $(GREEN)READY$(NONE)\n\n"

objectdir:
		@mkdir $(OBJ_DIR) 2> /dev/null || true

$(NAME): $(OBJS)
		@printf "\n\nObject Files: $(GREEN)READY$(NONE)\n"
		@printf "\nC O N V E R T E R : "
		@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -I $(INC_DIR) $(LIB)
		@printf "$(GREEN)READY$(NONE)\n\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
		@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)
		@printf "."

clean:
		@rm -rf obj

fclean: clean
		@rm -rf $(NAME)
		@rm -rf test_img/processed_image.bmp

re: fclean all

run: all
		@rm -rf test_img/processed_image.bmp
		@./converter ./test_img/test_2.bmp 969 551 DDCCBB ../palette_maker/test_palette/palette.hex

valgrind: all
		@rm -rf img/processed_image.bmp
		@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./palette_maker ./test_palette/10x10/ ./test_palette/palette.hex
