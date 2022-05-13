#include <fluf/drawing/texture.h>
#include <glad/glad.h>
#include <stb/stb_image.h>

using namespace fluf;

Texture::Texture(const FilePath& path)
	: m_renderer_id(0), m_filepath(path), m_local_buffer(nullptr), m_width(0), m_height(0), m_bpp(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_local_buffer = stbi_load(path.cstr(), &m_width, &m_height, &m_bpp, FLUF_IMAGE_CHANNELS);

	glGenTextures(1, &m_renderer_id);
	glBindTexture(GL_TEXTURE_2D, m_renderer_id);

	// these parameters need to be specified otherwise a black texture will be drawn
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// the last parameter can be nullptr if data is not loaded yet
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_local_buffer);
	unbind();

	if (m_local_buffer)
		stbi_image_free(m_local_buffer);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_renderer_id);
}

void Texture::bind(uint slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_renderer_id);
}

void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}