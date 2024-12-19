CC=gcc
CFLAGS=-I include
OBJ=main.o sed_operations.o utils.o

all: sed_simplified

sed_simplified: $(OBJ)
	$(CC) -o $@ $^

clean:
	rm -f $(OBJ) sed_simplified

test:
	./sed_simplified input.txt -r “old text” “new text”
   

