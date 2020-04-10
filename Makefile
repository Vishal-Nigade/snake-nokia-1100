CC=gcc

ODIR=obj
LDIR =../lib

LIBS=-lm

OBJ = Snake.c 


Snake: 
	@$(CC) --save-temps $(OBJ) -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	@rm -f *.o *.i *.s Snake 
