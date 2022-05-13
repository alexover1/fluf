#pragma once
#define GL_BYTE 0x1400
#define GL_UNSIGNED_BYTE 0x1401
#define GL_SHORT 0x1402
#define GL_UNSIGNED_SHORT 0x1403
#define GL_INT 0x1404
#define GL_UNSIGNED_INT 0x1405
#define GL_FLOAT 0x1406

// TODO: remove this ^

namespace fluf
{
	class Shader;
	class varray;
	class ibuffer;

	class Renderer
	{
	public:
		void draw_triangles(const varray& va, const ibuffer& ib, Shader& shader) const;
	};
}
