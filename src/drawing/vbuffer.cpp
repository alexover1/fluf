#include <fluf/drawing/vbuffer.h>
#include <glad/glad.h>

using namespace fluf;

vbuffer::vbuffer(const void* data, uint size)
{
	glGenBuffers(1, &m_renderer_id);
	glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

vbuffer::~vbuffer()
{
	glDeleteBuffers(1, &m_renderer_id);
}

void vbuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
}

void vbuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}