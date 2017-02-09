CFLAGS = -std=gnu++0x -lGL -lGLU -lglut -ljpeg -lpng -O2

main: build main.cpp build/vector_basics.o build/polygon3d.o build/globals.o build/building.o build/target.o imageLibrary/image.a 
	g++ $(CFLAGS) -o main main.cpp $(wildcard build/*.o) imageLibrary/image.a

build:
	mkdir build

build/vector_basics.o: vector_basics.cpp vector_basics.h
	g++ $(CFLAGS) -o $@ -c $<
build/polygon3d.o: polygon3d.cpp polygon3d.h
	g++ $(CFLAGS) -o $@ -c $<
build/globals.o: globals.cpp globals.h
	g++ $(CFLAGS) -o $@ -c $<
build/building.o: building.cpp building.h
	g++ $(CFLAGS) -o $@ -c $<
build/target.o: target.cpp target.h
	g++ $(CFLAGS) -o $@ -c $<

imageLibrary/image.a:
	cd imageLibrary; make;

clean:
	rm -f *.o
	rm -f build/*.o
	rm -f main

distclean: clean
	cd imageLibrary; make distclean
