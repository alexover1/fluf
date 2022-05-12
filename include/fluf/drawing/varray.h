#pragma once
#include <fluf/containers/vector.h>
#include <fluf/drawing/renderer.h>
#include "vbuffer.h"

namespace fluf
{
	struct vbufferelement
	{
		uint type;
		uint count;
		unsigned char normalized;

		static uint get_size_of_type(uint type)
		{
			switch (type)
			{
				case GL_FLOAT:			return 4;
				case GL_UNSIGNED_INT:	return 4;
				case GL_UNSIGNED_BYTE:	return 1;
			}
			FLUF_ASSERT(false, "varray.h: unexpected type");
			return 0;
		}
	};

	class vbufferlayout
	{
	private:
		Vector<vbufferelement> m_elements;
		uint m_stride;

	public:
		vbufferlayout()
			: m_stride(0) {}

		template<typename T>
		void push(uint count)
		{
			//static_assert(false);
		}

		template<>
		void push<float>(uint count)
		{
			m_elements.push_back(vbufferelement{ GL_FLOAT, count, GL_FALSE });
			m_stride += count * vbufferelement::get_size_of_type(GL_FLOAT);
		}

		template<>
		void push<uint>(uint count)
		{
			m_elements.push_back(vbufferelement{ GL_UNSIGNED_INT, count, GL_FALSE });
			m_stride += count * vbufferelement::get_size_of_type(GL_UNSIGNED_INT);
		}

		template<>
		void push<unsigned char>(uint count)
		{
			m_elements.push_back(vbufferelement{ GL_UNSIGNED_BYTE, count, GL_TRUE });
			m_stride += count * vbufferelement::get_size_of_type(GL_UNSIGNED_BYTE);
		}

		inline const Vector<vbufferelement> elements() const { return m_elements; }
		inline uint stride() const { return m_stride; }
	};

	class varray
	{
	private:
		uint m_renderer_id;
	public:
		varray();
		~varray();

		void add_buffer(const vbuffer& vb, const vbufferlayout& layout);

		void bind() const;
		void unbind() const;
	};
}
