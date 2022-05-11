#pragma once
#include <fluf/common.h>
#include <fluf/graphics.h>
#include <fluf/math/spatial.h>

namespace Fluf
{
#define RENDERER_MAX_SPRITES	15000
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	(RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES)
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX 0
#define SHADER_COLOR_INDEX 1

	class Batch
	{
	private:
		uint m_vao;
		uint m_vbo;
		VertexData* m_buffer;
		IndexBuffer* m_ibo;
		int m_index_count;

		void init();

	public:
		Batch();
		~Batch();

		void begin();
		void submit(const Renderable* renderable);
		void end();
		void flush();
	};
}