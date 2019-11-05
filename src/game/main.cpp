#include <memory>
#include "engine/window.h"
#include "engine/layered_renderer.h"

int main(int argc,char** args){
	if(!glfwInit()){
		printf("Unable to start glfw\n");
		exit(-1);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	std::shared_ptr<Window> window(new Window());
	window->create(640,480,"Tank Game");
	window->bind();

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		glfwTerminate();
		printf("Unable to load GL functions\n");
		exit(-2);
	}
	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );

	while(!window->shouldClose()){
		window->swapBuffers();
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}