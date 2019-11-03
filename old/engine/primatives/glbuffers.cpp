#include "glbuffers.h"

GLVertexBuffer::GLVertexBuffer(GLenum bufferType,GLenum usageStyle) : type(bufferType), usage(usageStyle){
	glGenBuffers(1,&bufferId);
}
GLVertexBuffer::~GLVertexBuffer(){
	glDeleteBuffers(1,&bufferId);
}

void GLVertexBuffer::bufferData(GLsizei size, const void* data){
	glBufferData(type, size, data, usage);
}
void GLVertexBuffer::bind(){
	glBindBuffer(type,bufferId);
}
GLuint GLVertexBuffer::id(){
	return bufferId;
}