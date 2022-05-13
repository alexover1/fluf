#pragma once
#include <fluf/common.h>

namespace fluf
{
	class ibuffer
	{
	private:
		uint m_renderer_id;
		uint m_count;

	public:
		ibuffer(const ushort* data, uint count);
		~ibuffer();

		void bind() const;
		void unbind() const;

		inline uint count() const { return m_count; }
	};
}
