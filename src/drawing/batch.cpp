#include <fluf/drawing/batch.h>
#include <GL/glew.h>
#include <cstddef>

using namespace Fluf;

Batch::Batch()
{
	init();
}

Batch::~Batch()
{
	delete m_ibo;
	glDeleteBuffers(1, &m_vbo);
}

void Batch::init()
{
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
	glEnableVertexAttribArray(SHADER_COLOR_INDEX);
	glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const void*)0);
	glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const void*)(offsetof(VertexData, VertexData::color)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	ushort* indices = new ushort[RENDERER_INDICES_SIZE];

	int offset = 0;
	for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
	{
		indices[i] = offset;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;

		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset + 0;

		offset += 4;
	}

	m_ibo = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

	glBindVertexArray(0);

	delete[] indices; // TODO: is this needed?
}

void Batch::begin()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	m_buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}

void Batch::submit(const Renderable* renderable)
{
	auto position = renderable->position();
	auto size = renderable->size();
	const Color& color = renderable->color();

	uint c = color.to_rgba();

	//m_buffer->vertex = position;
	vec3_dup(m_buffer->vertex, position);
	m_buffer->color = c;
	m_buffer++;

	//m_buffer->vertex = vec3{ position.x, position.y + size.y, position.z };
	vec3_dup(m_buffer->vertex, vec3{ position[0], position[1] + size[1], position[2]});
	m_buffer->color = c;
	m_buffer++;

	//m_buffer->vertex = vec3{ position[0] + size[0], position[1] + size[1], position[2]};
	vec3_dup(m_buffer->vertex, vec3{ position[0] + size[0], position[1] + size[1], position[2] });
	m_buffer->color = c;
	m_buffer++;

	//m_buffer->vertex = vec3{ position[0] + size[0], position[1], position[2]};
	vec3_dup(m_buffer->vertex, vec3{ position[0] + size[0], position[1], position[2] });
	m_buffer->color = c;
	m_buffer++;

	m_index_count += 6;
}

void Batch::end()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Batch::flush()
{
	glBindVertexArray(m_vao);
	m_ibo->bind();

	glDrawElements(GL_TRIANGLES, m_index_count, GL_UNSIGNED_SHORT, nullptr);

	m_ibo->unbind();
	glBindVertexArray(0);

	m_index_count = 0;
}