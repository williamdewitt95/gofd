#include "layered_renderer.h"

// =============================================================
// Drawable Object
// =============================================================
void DrawableObject::draw(){}

// =============================================================
// Layer
// =============================================================

void Layer::render(){
		glClear(GL_DEPTH_BUFFER_BIT);
		for( auto& object : objects ){
			object->draw();
		}
}
void Layer::addObject(std::shared_ptr<DrawableObject> object){
	objects.push_back(object);
}
void Layer::removeObject(int& index){
	objects.erase(objects.begin() + index); //potentially memory unsafe? does not check bounds?
}
std::shared_ptr<DrawableObject> Layer::getObject(int& index){
	return objects[index];
}
std::vector<std::shared_ptr<DrawableObject> >::size_type Layer::numberOfObjects(){
	return objects.size();
}

// =============================================================
// LayeredRenderer
// =============================================================

void LayeredRenderer::render(){
	for ( auto& layer : layers ){
		layer.second->render();
	}
}

void LayeredRenderer::addObject(int& layer,std::shared_ptr<DrawableObject> object){
	if(! hasLayer(layer) )
		layers[layer] = std::shared_ptr<Layer>( new Layer() );
	layers[layer]->addObject(object);
}
void LayeredRenderer::removeObject(int& layer,int& objectIndex){
	auto& layerV = layers.at(layer);
	layerV->removeObject(objectIndex);
	if(layerV->numberOfObjects() == 0)
		deleteLayer(layer);
}

std::shared_ptr<Layer> LayeredRenderer::getLayer(int& layer){
	return layers.at(layer);
}
void LayeredRenderer::deleteLayer(int& layer){
	layers.erase(layer);
}
std::map<int,std::shared_ptr<Layer> >::size_type LayeredRenderer::numberOfLayers(){
	return layers.size();
}
bool LayeredRenderer::hasLayer(int& layer){
	// doing a compare just to keep the type as a bool
	return layers.count(layer) == 1;
}