#ifndef glop_tesselator
#define glop_tesselator

#include <vector>
#include "glad/glad.h"
#include <GL/glu.h>
#include "primatives/polygon3d.h"

class Tesselator{
public:
	Tesselator() = default; // no settings to figure out at this time
	void inPlaceTesselate(Polygon3d&); // modifies the passed polygon
};

#endif //glop_tesselator