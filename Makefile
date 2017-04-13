
CC       = g++
CFLAGS   = -std=gnu++0x 
OPTFLAGS = -O2

# Setup names for custom directories -- make sure there are no spaces after the directory names
BUILD_DIR   = build


# Setup objects  (add new object files here an create a target line for them below 
OBJS        = vector_basics.o polygon3d.o globals.o \
              building.o tank.o target.o projectile.o ai.o\
              drawableObject.o
BUILD_OBJS  = $(addprefix $(BUILD_DIR)/, $(OBJS))


# System librarires to be linked
LDFLAGS  = -lGL -lGLU -lglut -lGLEW libSOIL.a

#the available buildings that we depend on when building
BUILDINGS = buildings/generic1.cpp buildings/genericOctogon.cpp buildings/apartmentHighrise.cpp
#extra decoration bits for buildings like windows
BUILDING_EXTRAS = buildings/window1.cpp

all: build gofd tags

build:
	mkdir build

# The new executable target will be called gofd
gofd: main.o $(BUILD_OBJS) 
	$(CC) $(CFLAGS) -o gofd main.o $(BUILD_OBJS) $(LDFLAGS)

# These are the object file targets 
main.o: main.cpp  
	$(CC) $(CFLAGS) main.cpp -c -o main.o   

$(BUILD_DIR)/vector_basics.o: vector_basics.cpp vector_basics.h
	$(CC) $(CFLAGS) $(OPTFLAGS) vector_basics.cpp -c  -o $(BUILD_DIR)/vector_basics.o 

$(BUILD_DIR)/polygon3d.o: polygon3d.cpp polygon3d.h
	$(CC) $(CFLAGS) $(OPTFLAGS) polygon3d.cpp -c -o $(BUILD_DIR)/polygon3d.o 

$(BUILD_DIR)/globals.o: globals.cpp globals.h
	$(CC) $(CFLAGS) $(OPTFLAGS) globals.cpp -c -o $(BUILD_DIR)/globals.o 

$(BUILD_DIR)/building.o: building.cpp building.h $(BUILDINGS) $(BUILDING_EXTRAS)
	$(CC) $(CFLAGS) $(OPTFLAGS) building.cpp -c -o $(BUILD_DIR)/building.o 

$(BUILD_DIR)/tank.o: tank.cpp tank.h 
	$(CC) $(CFLAGS) $(OPTFLAGS) tank.cpp -c -o $(BUILD_DIR)/tank.o 

$(BUILD_DIR)/target.o: target.cpp target.h
	$(CC) $(CFLAGS) $(OPTFLAGS) target.cpp -c -o $(BUILD_DIR)/target.o 

$(BUILD_DIR)/projectile.o: projectile.cpp projectile.h
	$(CC) $(CFLAGS) $(OPTFLAGS) projectile.cpp -c -o $(BUILD_DIR)/projectile.o 

$(BUILD_DIR)/ai.o: ai.cpp ai.h
	$(CC) $(CFLAGS) $(OPTFLAGS) ai.cpp -c -o $(BUILD_DIR)/ai.o

$(BUILD_DIR)/screencapture.o: screencapture.c
	$(CC) $(CFLAGS) $(OPTFLAGS) screencapture.c -c -o $(BUILD_DIR)/screencapture.o 

$(BUILD_DIR)/drawableObject.o: drawableObject.cpp drawableObject.h
	$(CC) $(CFLAGS) $(OPTFLAGS) drawableObject.cpp -c -o $(BUILD_DIR)/drawableObject.o 

# Drop into the subdirectory to create the image library

clean:
	rm -f *.o
	rm -f build/*.o
	rm -f gofd 

distclean: clean
	rm -rf build
	rm -f tags

tags: *.cpp *.h
	ctags *.cpp *.h
