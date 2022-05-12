#pragma once
#include <fluf/common.h>
#include <fluf/math.h>

namespace fluf
{
	struct Color
	{
		u8 r;
		u8 g;
		u8 b;
		u8 a;

		constexpr Color()
			: r(0), g(0), b(0), a(0) {}

		constexpr Color(int rgb)
			: r((u8)((rgb & 0xFF0000) >> 16))
			, g((u8)((rgb & 0x00FF00) >> 8))
			, b((u8)(rgb & 0x0000FF))
			, a(255) {}

		constexpr Color(int rgb, float alpha)
			: r((int)(((u8)((rgb & 0xFF0000) >> 16))* alpha))
			, g((int)(((u8)((rgb & 0x00FF00) >> 8))* alpha))
			, b((int)(((u8)(rgb & 0x0000FF))* alpha))
			, a((int)(255 * alpha)) {}

		constexpr Color(u8 r, u8 g, u8 b)
			: r(r)
			, g(g)
			, b(b)
			, a(255) {}

		constexpr Color(u8 r, u8 g, u8 b, u8 a)
			: r(r)
			, g(g)
			, b(b)
			, a(a) {}

		constexpr Color(const vec3& vec)
			: r((int)(vec[0] * 255))
			, g((int)(vec[1] * 255))
			, b((int)(vec[2] * 255))
			, a((int)(255)) {}

		constexpr Color(const vec3& vec, float alpha)
			: r((int)(vec[0] * alpha * 255))
			, g((int)(vec[1] * alpha * 255))
			, b((int)(vec[2] * alpha * 255))
			, a((int)(alpha * 255)) {}

		constexpr Color(const vec4& vec)
			: r((int)(vec[0] * 255))
			, g((int)(vec[1] * 255))
			, b((int)(vec[2] * 255))
			, a((int)(vec[3] * 255)) {}

		// Premultiplies the Color
		constexpr void premultiply()
		{
			r = r * a / 255;
			g = g * a / 255;
			b = b * a / 255;
		}

		// Converts the Color to a Vec3 (RGB)
		constexpr vec3& to_vec3() const
		{
			vec3 vec = { r / 255.0f, g / 255.0f, b / 255.0f };
			return vec;
		}

		// Converts the Color to a Vec4 (RGBA)
		constexpr vec4& to_vec4() const
		{
			vec4 vec = { r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f };
			return vec;
		}

		// Convers the Color to a u32
		constexpr u32 to_rgba() const
		{
			return
				((u32)a << 24) |
				((u32)b << 16) |
				((u32)g << 8) |
				(u32)r;
		}

		// Convers the Color to a u32
		constexpr u32 to_rgb() const
		{
			return
				((u32)r << 16) |
				((u32)g << 8) |
				(u32)b;
		}

		// Returns a RGBA Color representation of the integer value
		static constexpr Color from_rgba(u32 value)
		{
			return
			{
				(u8)((value & 0xFF000000) >> 24),
				(u8)((value & 0x00FF0000) >> 16),
				(u8)((value & 0x0000FF00) >> 8),
				(u8)((value & 0x000000FF))
			};
		}

		// Returns a RGB Color representation of the integer value, with Alpha = 255
		static constexpr Color from_rgb(u32 value)
		{
			return
			{
				(u8)((value & 0xFF0000) >> 16),
				(u8)((value & 0x00FF00) >> 8),
				(u8)((value & 0x0000FF))
			};
		}

		// Lerps between two colors
		static constexpr Color lerp(Color a, Color b, float amount)
		{
			if (amount < 0) amount = 0;
			if (amount > 1) amount = 1;

			return Color(
				(u8)(a.r + (b.r - a.r) * amount),
				(u8)(a.g + (b.g - a.g) * amount),
				(u8)(a.b + (b.b - a.b) * amount),
				(u8)(a.a + (b.a - a.a) * amount)
			);
		}

		// Mutliplties the Color
		constexpr Color operator*(float multiply) const
		{
			return Color(
				(int)(r * multiply),
				(int)(g * multiply),
				(int)(b * multiply),
				(int)(a * multiply));
		}

		// assignment from int
		constexpr Color& operator= (int rgb)
		{
			r = (u8)((rgb & 0xFF0000) >> 16);
			g = (u8)((rgb & 0x00FF00) >> 8);
			b = (u8)(rgb & 0x0000FF);
			a = 255;
			return *this;
		}

		constexpr bool operator ==(const Color& rhs) const
		{
			return r == rhs.r && g == rhs.g && b == rhs.b && a == rhs.a;
		}

		constexpr bool operator !=(const Color& rhs) const
		{
			return r != rhs.r || g != rhs.g || b != rhs.b || a != rhs.a;
		}

		static const Color transparent;
		static const Color white;
		static const Color black;
		static const Color red;
		static const Color green;
		static const Color blue;
		static const Color yellow;
		static const Color orange;
		static const Color purple;
		static const Color teal;
	};

	inline const Color Color::transparent = Color(0, 0, 0, 0);
	inline const Color Color::white = Color(255, 255, 255);
	inline const Color Color::black = Color(0, 0, 0);
	inline const Color Color::red = Color(255, 0, 0);
	inline const Color Color::green = Color(0, 255, 0);
	inline const Color Color::blue = Color(0, 0, 255);
	inline const Color Color::yellow = Color(255, 255, 0);
	inline const Color Color::purple = Color(255, 0, 255);
	inline const Color Color::teal = Color(0, 255, 255);
}