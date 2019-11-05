#include "window.h"

Window::Window() : handle{NULL},fbSize{0,0},wSize{0,0},resizeFBFunc{NULL},resizeFunc{NULL} {}

Window::~Window(){
	if(handle){ // we have created a window
		windowObjects.erase(handle);
		glfwDestroyWindow(handle);
	}
}


void Window::create(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share){
	this->handle = glfwCreateWindow(width,height,title,monitor,share);
	if (handle){
		windowObjects[handle] = this;
		glfwSetWindowSizeCallback(handle,wSizeCallback);
		glfwSetFramebufferSizeCallback(handle,fbSizeCallback);
	}
}
void Window::bind(){
	glfwMakeContextCurrent(handle);
}
GLFWwindow* Window::id(){
	return handle;
}
void Window::swapBuffers(){
	glfwSwapBuffers(handle);
}


void Window::show(){
	glfwShowWindow(handle);
}
void Window::hide(){
	glfwHideWindow(handle);
}


bool Window::shouldClose(){
	return glfwWindowShouldClose(handle);
}
void Window::askToClose(){
	glfwSetWindowShouldClose(handle,true);
}


Window::SIZE_T Window::framebufferSize(){
	return fbSize;
}
Window::SIZE_T Window::windowSize(){
	return wSize;
}
void Window::resizeFBCallback(GLFWframebuffersizefun func){
	resizeFBFunc = func;
}
void Window::resizeCallback(GLFWwindowsizefun func){
	resizeFunc = func;
}


void Window::fbSizeCallback(GLFWwindow* handle, int width, int height){
	// This gets called by GLFW - We need to update information and propogate the event
	Window* win = Window::windowObjects.at(handle);
	win->fbSize.x = width;
	win->fbSize.y = height;
	if (win->resizeFBFunc){
		win->resizeFBFunc(handle,width,height);
	}
}
void Window::wSizeCallback(GLFWwindow* handle, int width, int height){
	// This gets called by GLFW - We need to update information and propogate the event
	Window* win = Window::windowObjects.at(handle);
	win->wSize.x = width;
	win->wSize.y = height;
	if (win->resizeFunc){
		win->resizeFunc(handle,width,height);
	}
}