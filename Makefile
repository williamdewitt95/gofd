CFLAGS = -std=gnu++0x -lGL -lGLU -lglut -ljpeg -lpng -O2

main: build main.cpp build/vector_basics.o build/polygon3d.o build/globals.o build/building.o imageLibrary/image.a
	g++ -o main main.cpp $(wildcard build/*.o) imageLibrary/image.a $(CFLAGS)

build:
	mkdir build

build/vector_basics.o: vector_basics.cpp vector_basics.h
	g++ -o $@ -c $< $(CFLAGS)
build/polygon3d.o: polygon3d.cpp polygon3d.h
	g++ -o $@ -c $< $(CFLAGS)
build/globals.o: globals.cpp globals.h
	g++ -o $@ -c $< $(CFLAGS)
build/building.o: building.cpp building.h
	g++ -o $@ -c $< $(CFLAGS)

imageLibrary/image.a:
	cd imageLibrary; make;

clean:
	rm -f *.o
	rm -f build/*.o
	rm -f main

distclean: clean
	cd imageLibrary; make distclean
