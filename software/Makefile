SRC=main.c converter.c file_io.c
INC=-I ./includes/
OBJ=$(SRC:.cpp=.o)
EXE=converter
CC=gcc
CFLAGS=-c -Wall -Wextra
LDFLAGS=

all: $(SRC) $(EXE)
	
$(EXE): $(OBJ) 
	$(CC) $(LDFLAGS) $(OBJ) -o $@

$(OBJECTS):
	$(CC) $(CFLAGS) $(SRC) -o $(OBJ) $(INC)

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(EXE)

re: fclean all
