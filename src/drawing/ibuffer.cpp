#include <fluf/drawing/ibuffer.h>
#include <fluf/drawing/renderer.h>

using namespace fluf;

ibuffer::ibuffer(const uint* data, uint count)
	: m_count(count)
{
	glGenBuffers(1, &m_renderer_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint), data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

ibuffer::~ibuffer()
{
	glDeleteBuffers(1, &m_renderer_id);
}

void ibuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id);
}

void ibuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}