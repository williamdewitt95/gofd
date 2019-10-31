
CC       = g++
CFLAGS   = -std=gnu++0x 
OPTFLAGS = -O2

# Setup names for custom directories -- make sure there are no spaces after the directory names
BUILD_DIR   = build

# Setup objects  (add new object files here an create a target line for them below 
OBJS        = vector_basics.o polygon3d.o globals.o \
              building.o tank.o target.o projectile.o ai.o glm.o \
              drawableObject.o hud.o collisions.o skybox.o \
              groundbox.o screencapture.o main.o

BUILD_OBJS  = $(addprefix $(BUILD_DIR)/, $(OBJS))

# System librarires to be linked
LDFLAGS  = -lGL -lGLU -lglfw libSOIL.a

#the available buildings that we depend on when building
BUILDINGS = buildings/generic1.cpp buildings/genericOctogon.cpp buildings/apartmentHighrise.cpp
#extra decoration bits for buildings like windows
BUILDING_EXTRAS = buildings/window1.cpp

all: build wipe gofd

build:
	mkdir build
	mkdir screenshots

wipe:
	rm -f screenshots/*.tga

# The new executable target will be called gofd
gofd: $(BUILD_OBJS) 
	$(CC) $(CFLAGS) -o gofd $(BUILD_OBJS) $(LDFLAGS)

# These are the object file targets
$(BUILD_DIR)/%.o: %.cpp %.h globals.h
	$(CC) $(CFLAGS) $(OPTFLAGS) $< -c -o $@
$(BUILD_DIR)/%.o: %.cpp globals.h
	$(CC) $(CFLAGS) $(OPTFLAGS) $< -c -o $@

$(BUILD_DIR)/building.o: building.cpp building.h globals.h $(BUILDINGS) $(BUILDING_EXTRAS)
	$(CC) $(CFLAGS) $(OPTFLAGS) building.cpp -c -o $(BUILD_DIR)/building.o 

# Drop into the subdirectory to create the image library

movie:
	ffmpeg -r 60 -s 1920x1080 -i ./screenshots/Plot-%07d.tga -vcodec libx264 -crf 25 -pix_fmt yuv420p gofd_movie.mp4

clean:
	rm -f *.o
	rm -f build/*.o
	rm -f gofd
	rm -f screenshots/*.tga 

distclean: clean
	rm -rf build
	rm -rf screenshots
	rm -f tags
