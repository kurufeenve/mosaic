
SRC 	=	  converter.c		\
 
INC		=	  inc/conveerter.h				\

SRC_DIR	=	  ./src/
OBJ_DIR	=	  ./obj/
INC_DIR	=	  ./inc/
NAME	=	  converter
CFLAG	=	  -Werror -Wextra -Wall
LIB		=	  -L./libft/ -lft libft/libft.a
CC		=	  gcc

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
		@printf "\nCONVERTER: "
		@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -I $(INC_DIR) $(LIB)
		@printf "$(GREEN)READY$(NONE)\n\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
		@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)
		@printf "."

clean:
		@rm -rf obj

fclean: clean
		@rm -rf $(NAME)
		@rm -rf img/processed_image.bmp

re: fclean all
