#ifndef GL_BUFFERS
#define GL_BUFFERS
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

class GLVertexBuffer{
	GLuint bufferId;
public:
	const GLenum type;
	const GLenum usage;
	GLVertexBuffer(GLenum bufferType,GLenum usageStyle);
		//type is GL_ARRAY_BUFFER or GL_ELEMENT_ARRAY_BUFFER
		//usage is GL_STATIC_DRAW GL_STATIC_READ GL_STATIC_COPY GL_DYNAMIC_DRAW GL_DYNAMIC_READ GL_DYNAMIC_COPY GL_STREAM_DRAW GL_STREAM_READ GL_STREAM_COPY
	~GLVertexBuffer();
	GLuint id();
	void bind(); // bind buffer to current context - same as glBindBuffer()
	void bufferData(GLsizei size, const void* data);
};

#endif //GL_BUFFERS