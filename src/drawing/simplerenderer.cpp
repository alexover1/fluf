#include <fluf/drawing/simplerenderer.h>
#include <GL/glew.h>

using namespace Fluf;

void SimpleRenderer::submit(const Renderable* renderable)
{
	m_render_queue.push_back((StaticSprite*)renderable);
}


void SimpleRenderer::flush()
{
	while (!m_render_queue.empty())
	{
		const StaticSprite* sprite = m_render_queue.front();
		auto vao = sprite->vao();
		auto ibo = sprite->ibo();

		vao->bind();
		ibo->bind();

		//Get position
		auto pos = sprite->position();
		float x = pos[0], y = pos[1], z = pos[2];

		// Set matrix to position
		mat4x4 m;
		mat4x4_translate(m, x, y, z);

		// Render
		sprite->shader().set_uniform_mat4("ml_matrix", m);
		glDrawElements(GL_TRIANGLES, ibo->count(), GL_UNSIGNED_SHORT, nullptr);

		vao->unbind();
		ibo->unbind();

		m_render_queue.pop_front();
	}
}