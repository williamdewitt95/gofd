#ifndef glop_layeredRenderer
#define glop_layeredRenderer

// #############################################################
//   DRAWABLE OBJECT
// #############################################################
// This is an interface class.
// You should sub-class this for every object that you want to
// shove into the higher layers.
// #############################################################

#include "glad/glad.h"
#include <vector>
#include <map>
#include <memory>

class DrawableObject{
public:
	virtual void draw();
};

class Layer{
protected:
	std::vector<std::shared_ptr<DrawableObject> > objects;
public:
	typedef std::vector<std::shared_ptr<DrawableObject> >::size_type size_type;
	Layer() = default;
	void render();
	void addObject(std::shared_ptr<DrawableObject>);
	void removeObject(int& objectIndex);
	std::shared_ptr<DrawableObject> getObject(int& index);
	size_type numberOfObjects();
};

class LayeredRenderer{
protected:
	std::map<int,std::shared_ptr<Layer> > layers;
public:
	typedef std::map<int,std::shared_ptr<Layer> >::size_type size_type;
	LayeredRenderer() = default;
	void render();
	void addObject(int& layer,std::shared_ptr<DrawableObject>);
	void removeObject(int& layer,int& objectIndex);

	std::shared_ptr<Layer> getLayer(int& layer);
	void deleteLayer(int& layer);
	size_type numberOfLayers();
	bool hasLayer(int& layer);
};

#endif



// =================================================================
// Thinking about usability - Minimaps
// They need to have a viewport specified to make them only appear in the
// corner of the window. This means we need a second object called Layer
// that holds the objects and information about the viewport it is using.
// But then we hit the weirdness of wanting the viewport to be sticky to
// a corner for a mini-map. Will this logic be part of the game specific
// code or should this rendering manager handle that? If we handle it here
// then we need to have a callback to be notified directly from a window
// that a resize has happened, and we need to modify all the layers, but
// we will also need to know if the sticky behavior is deisred, or perhaps
// the viewport should be resized as a percentage of the window resize.

// This is probably better left to the client code to handle info updates
// but we are still going to need the layer object to hold viewport info


// =================================================================
// Things to be added as features
// bool skipDrawing - turns on or off the loop of drawing the objects
// int width,height,startX,startY - viewport size
//     - consider making it percentage and depend on window size?
//     - bad idea to couple windows and layers - make the layer only apply its viewport to the current drawing context
//     - issue, how to do a reset?  maybe static ints that are set with setDefaultViewport()
//          - but now this will bifurcate the object responsible for setting the viewport and the LayerManager will need to track who sets the viewport to something different
//     - TBD
// GLenum clearBits - the bits passed to glClear when drawing the layer
//     - lets you clear depth or depth+color or more
// support for ranged for loops to make iterating updates simpler