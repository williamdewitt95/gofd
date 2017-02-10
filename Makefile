CC       = g++
CFLAGS   = -std=gnu++0x 
OPTFLAGS = -O2
LDFLAGS  = -lGL -lGLU -lglut -ljpeg -lpng
BUILD_DIR   = build 
IMAGE_DIR = imageLibrary 
OBJS        = $(BUILD_DIR)/vector_basics.o $(BUILD_DIR)/polygon3d.o $(BUILD_DIR)/globals.o \
              $(BUILD_DIR)/building.o $(BUILD_DIR)/tank.o $(BUILD_DIR)/target.o 
LIBS        = $(IMAGE_DIR)/image.a

all: build gofd

gofd: main.o $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) -o gofd main.o $(OBJS) $(LIBS) $(LDFLAGS)

main.o: main.cpp  
	$(CC) $(CFLAGS) main.cpp -c   

build:
	mkdir build

$(BUILD_DIR)/vector_basics.o: vector_basics.cpp vector_basics.h
	$(CC) $(CFLAGS) $(OPTFLAGS) -c $(BUILD_DIR)/vector_basics.o 

$(BUILD_DIR)/polygon3d.o: polygon3d.cpp polygon3d.h
	$(CC) $(CFLAGS) $(OPTFLAGS) -c $(BUILD_DIR)/polygon3d.o 

$(BUILD_DIR)/globals.o: globals.cpp globals.h
	$(CC) $(CFLAGS) $(OPTFLAGS) -c $(BUILD_DIR)/globals.o 

$(BUILD_DIR)/building.o: building.cpp building.h
	$(CC) $(CFLAGS) $(OPTFLAGS) -c $(BUILD_DIR)/building.o 

$(BUILD_DIR)/tank.o: tank.cpp tank.h
	$(CC) $(CFLAGS) $(OPTFLAGS) -c $(BUILD_DIR)/tank.o 

$(BUILD_DIR)/target.o: target.cpp target.h
	$(CC) $(CFLAGS) $(OPTFLAGS) -c $(BUILD_DIR)/target.o 

$(IMAGE_DIR)/image.a:
	cd $(IMAGE_DIR); make;

clean:
	rm -f *.o
	rm -f build/*.o
	rm -f main

distclean: clean
	cd imageLibrary; make distclean
