
CC       = g++
CFLAGS   = -std=gnu++0x
OPTFLAGS = -Og
INCLUDES = -Iglad/include -Igame_old -Iprimatives


# Setup names for custom directories -- make sure there are no spaces after the directory names
BUILD_DIR   = build

# Setup objects  (add new object files here an create a target line for them below 
OBJS        = vector_basics.o polygon3d.o globals.o \
              building.o tank.o target.o projectile.o ai.o glm.o \
              drawableObject.o hud.o skybox.o collisions.o \
              groundbox.o main.o glbuffers.o \
              glad.o

BUILD_OBJS  = $(addprefix $(BUILD_DIR)/, $(OBJS))

# System librarires to be linked
LDFLAGS  = -lGL -lGLU -lglfw -ldl game_old/libSOIL.a

#the available buildings that we depend on when building
BUILDINGS        = generic1.cpp genericOctogon.cpp apartmentHighrise.cpp
BUILDING_EXTRAS  = window1.cpp
BUILDINGS       := $(addprefix game_old/buildings/, $(BUILDINGS))
BUILDING_EXTRAS := $(addprefix game_old/buildings/, $(BUILDING_EXTRAS))

CFLAGS := $(CFLAGS) $(INCLUDES)

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
$(BUILD_DIR)/%.o: game_old/%.cpp game_old/%.h
	$(CC) $(CFLAGS) $(OPTFLAGS) $< -c -o $@
$(BUILD_DIR)/%.o: primatives/%.cpp primatives/%.h
	$(CC) $(CFLAGS) $(OPTFLAGS) $< -c -o $@
$(BUILD_DIR)/%.o: game_old/%.cpp
	$(CC) $(CFLAGS) $(OPTFLAGS) $< -c -o $@
$(BUILD_DIR)/%.o: glad/src/%.c
	$(CC) $(CFLAGS) $(OPTFLAGS) $< -c -o $@

$(BUILD_DIR)/building.o: game_old/building.cpp game_old/building.h $(BUILDINGS) $(BUILDING_EXTRAS)
	$(CC) $(CFLAGS) $(OPTFLAGS) $< -c -o $(BUILD_DIR)/building.o



clean:
	rm -f *.o
	rm -f build/*.o
	rm -f gofd
	rm -f screenshots/*.tga 

distclean: clean
	rm -rf build
	rm -rf screenshots
	rm -f tags
