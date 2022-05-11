#include <fluf/graphics.h>
#include <GL/glew.h>

using namespace Fluf;

// TODO: this needs to be adapted for multiple renderers

Buffer::Buffer(float* data, int count, uint component_count)
	: m_component_count(component_count)
{
	glGenBuffers(1, &m_id);
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Buffer::~Buffer()
{
	glDeleteBuffers(1, &m_id);
}

void Buffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
}


void Buffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

IndexBuffer::IndexBuffer(ushort* data, int count)
	: m_count(count)
{
	glGenBuffers(1, (GLuint*) &m_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(ushort), data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, (GLuint*) &m_id);
}

void IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void IndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_array_id);
}

VertexArray::~VertexArray()
{
	for (int i = 0; i < m_buffers.size(); i++)
		delete m_buffers[i];

	glDeleteVertexArrays(1, &m_array_id);
}

void VertexArray::add_buffer(Buffer* buffer, uint index)
{
	bind();
	buffer->bind();

	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, buffer->component_count(), GL_FLOAT, GL_FALSE, 0, 0);

	buffer->unbind();
	unbind();
}

void VertexArray::bind() const
{
	glBindVertexArray(m_array_id);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}