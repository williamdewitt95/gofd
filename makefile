CC = gcc
CFLAGS = 
COPTFLAGS =
LIBFLAGS = -lglut -lGLU -lGL


polygon : template.o
	$(CC) template.o -o template $(LIBFLAGS)

polygon.o : template.c
	$(CC) $(CFLAGS) $(COPTFLAGS) -c template.c

clean :
	rm *.o
pristine :
	rm *.o
	touch *.c
ctags :
	ctags *.c
