#pragma once
#include <fluf/containers/str.h>

#define FLUF_IMAGE_CHANNELS 4

namespace fluf
{
	class Texture
	{
	private:
		uint m_renderer_id;
		FilePath m_filepath;
		unsigned char* m_local_buffer;
		int m_width, m_height, m_bpp;

	public:
		Texture(const FilePath& path);
		~Texture();

		void bind(uint slot = 0) const;
		void unbind() const;

		inline int width() const { return m_width; }
		inline int height() const { return m_height; }
	};

}