CC = g++
CFLAGS = 
COPTFLAGS =
LIBFLAGS = -lglut -lGLU -lGL


main : main.o
	$(CC) main.o -o main $(LIBFLAGS)

main.o : main.cpp
	$(CC) $(CFLAGS) $(COPTFLAGS) -c main.cpp

clean :
	rm *.o
pristine :
	rm *.o
	touch *.c
ctags :
	ctags *.c
