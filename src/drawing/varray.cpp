#include <fluf/drawing/varray.h>
#include <glad/glad.h>

using namespace fluf;

varray::varray()
{
	glGenVertexArrays(1, &m_renderer_id);
}

varray::~varray()
{
	glDeleteVertexArrays(1, &m_renderer_id);
}

void varray::add_buffer(const vbuffer& vb, const vbufferlayout& layout)
{
	bind();
	vb.bind();

	const auto& elements = layout.elements();
	uint offset = 0;
	for (uint i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.stride(), (const void*)offset);
		offset += element.count * vbufferelement::get_size_of_type(element.type);
	}
}

void varray::bind() const
{
	glBindVertexArray(m_renderer_id);
}

void varray::unbind() const
{
	glBindVertexArray(0);
}