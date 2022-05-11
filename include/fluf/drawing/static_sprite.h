#pragma once
#include <fluf/graphics.h>
#include <fluf/drawing/shader.h>
#include <fluf/math/spatial.h>
#include <fluf/math/color.h>

namespace Fluf
{
	class StaticSprite : public Renderable
	{
	private:
		VertexArray* m_vertex_array;
		IndexBuffer* m_index_buffer;
		Shader& m_shader;

	public:
		StaticSprite(float x, float y, float width, float height, const vec4& color, Shader& shader);
		~StaticSprite();

		inline const VertexArray* vao() const { return m_vertex_array; }
		inline const IndexBuffer* ibo() const { return m_index_buffer; }

		inline const Shader& shader() const { return m_shader; }
	};
}