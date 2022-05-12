#pragma once
#include <fluf/common.h>

namespace fluf
{
	class vbuffer
	{
	private:
		uint m_renderer_id;

	public:
		vbuffer(const void* data, uint size);
		~vbuffer();

		void bind() const;
		void unbind() const;
	};
}
