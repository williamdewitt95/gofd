#ifndef glop_Window
#define glop_Window

// https://www.glfw.org/docs/latest/group__window.html
// This is a simple thin wrapper around a window from GLFW.
// Mostly this is to auto-magically handle the lifetime of
// the window and just have a few handy functions.

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <map>

class Window{
public:
	struct SIZE_T{int x,y;};
protected:
	GLFWwindow* handle;
	SIZE_T fbSize;
	SIZE_T wSize;
	static std::map<GLFWwindow*,Window*> windowObjects; // Objects add themselves on create() and remove themselves in the destructor
	static void fbSizeCallback(GLFWwindow *, int, int);
	static void wSizeCallback(GLFWwindow *, int, int);
	GLFWframebuffersizefun resizeFBFunc;
	GLFWwindowsizefun resizeFunc;
public:
	Window();
	~Window(); // calls glfwDestroyWindow() and removes itself from windowObjects map
	Window(const Window&) = delete; // No copies allowed!
	Window& operator=(const Window&) = delete; // No really, it will break things

	void create(int width, int height, const char *title, GLFWmonitor *monitor = NULL, GLFWwindow *share = NULL);
	void bind(); // make the context and framebuffer current for drawing into
	GLFWwindow* id(); // get the ID that you can pass to glfw functions
	void swapBuffers(); // update the window after being done drawing

	void show(); // make it visable
	void hide(); // hide the window but don't close the window

	bool shouldClose();
	void askToClose();

	SIZE_T framebufferSize(); // Use this for setting up your GL system such as viewport
	SIZE_T windowSize();
	void resizeFBCallback(GLFWframebuffersizefun); // give callbacks for when the window resizes
	void resizeCallback(GLFWwindowsizefun);        // use these so that we can cache the sizes ourself
};

#endif