#pragma once
#include <fluf/common.h>
#include <fluf/math/spatial.h>
#include <fluf/math/color.h>
#include <vector>

namespace Fluf
{
	class Buffer
	{
	private:
		uint m_id;
		unsigned int m_component_count;

	public:
		Buffer(float* data, int count, uint component_count);
		~Buffer();

		inline uint component_count() const { return m_component_count; }

		void bind() const;
		void unbind() const;
	};

	class IndexBuffer
	{
	private:
		int m_id;
		int m_count;

	public:
		IndexBuffer(ushort* data, int count);
		~IndexBuffer();

		inline uint count() const { return m_count; }

		void bind() const;
		void unbind() const;
	};

	class VertexArray
	{
	private:
		uint m_array_id;
		std::vector<Buffer*> m_buffers;

	public:
		VertexArray();
		~VertexArray();

		void add_buffer(Buffer* buffer, uint index);
		void bind() const;
		void unbind() const;
	};

	struct VertexData
	{
		vec3 vertex;
		unsigned int color;
	};

	class Renderable
	{
	public:
		vec3 m_position;
		vec2 m_size;
		Color m_color;

		Renderable(vec3 position, vec2 size, Color color)
			: m_color(color)
		{
			vec3_dup(m_position, position);
			vec2_dup(m_size, size);
		}

		virtual ~Renderable() { }

		inline const vec3& position() const { return m_position; }
		inline const vec2& size() const { return m_size; }
		inline const Color& color() const { return m_color; }
	};
}