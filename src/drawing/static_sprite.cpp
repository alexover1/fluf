#include <fluf/drawing/static_sprite.h>

using namespace Fluf;

StaticSprite::StaticSprite(float x, float y, float width, float height, const vec4& color, Shader& shader)
	: Renderable(vec3{x, y, 0}, vec2{width, height}, Color(color)), m_shader(shader)
{
	m_vertex_array = new VertexArray();
	float vertices[] =
	{
		0, 0, 0,
		0, height, 0,
		width, height, 0,
		width, 0, 0,
	};

	float colors[] =
	{
		color[0], color[1], color[2], color[3],
		color[0], color[1], color[2], color[3],
		color[0], color[1], color[2], color[3],
		color[0], color[1], color[2], color[3],
	};

	m_vertex_array->add_buffer(new Buffer(vertices, 4 * 3, 3), 0);
	m_vertex_array->add_buffer(new Buffer(colors, 4 * 4, 4), 1);

	ushort indices[] = { 0, 1, 2, 2, 3, 0 };
	m_index_buffer = new IndexBuffer(indices, 6);
}

StaticSprite::~StaticSprite()
{
	delete m_vertex_array;
	delete m_index_buffer;
}