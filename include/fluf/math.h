#pragma once
#include <fluf/common.h>

namespace fluf
{
	struct Vec2
	{
		union
		{
			struct { float x, y; };
			float xy[2];
		};

		Vec2() : Vec2(0, 0) { }

		Vec2(float x, float y)
			: x(x), y(y)
		{
		}

		inline void log()
		{
			Log::info("Vec2: (%f, %f)", x, y);
		}
	};

	struct Vec3
	{
		union
		{
			struct { float x, y, z; };
			struct { float r, g, b; };
			float xy[2];
			float xyz[3];
		};

		Vec3() : Vec3(0, 0, 0) { }

		Vec3(float x, float y, float z) 
			: x(x), y(y), z(z)
		{
		}

		inline void log()
		{
			Log::info("Vec3: (%f, %f, %f)", x, y, z);
		}
	};

	struct Vec4
	{
		union
		{
			struct { float x, y, z, w; };
			struct { float r, g, b, a; };
			float xy[2];
			float xyz[3];
			float xyzw[4];
		};

		Vec4() : Vec4(0, 0, 0, 0) { }

		Vec4(float x, float y, float z, float w)
			: x(x), y(y), z(z), w(w)
		{
		}

		inline void log()
		{
			Log::info("Vec4: (%f, %f, %f, %f)", x, y, z, w);
		}
	};
}