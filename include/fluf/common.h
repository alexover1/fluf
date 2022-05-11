#pragma once

#include <new>
#include <utility> // for std::move and std::size_t

// Asserts
#if defined(DEBUG) || defined(_DEBUG)
#	include<stdlib.h>
#	define FLUF_ASSERT(condition, msg) \
	if (!(condition)) { Fluf::Log::error("%s\n\tin %s:%d", (msg), __FILE__, __LINE__); abort(); }
#else
#	define FLUF_ASSERT(condition, msg) \
	if (!(condition)) { Fluf::Log::error("%s\n\tin %s:%d", (msg), __FILE__, __LINE__); }
#endif

// Numeric Types
#include <stdint.h>    // for integer types
#include <stddef.h>    // for size_t type
namespace Fluf
{
	// Numeric Types
	using i8 = int8_t;
	using i16 = int16_t;
	using i32 = int32_t;
	using i64 = int64_t;
	using u8 = uint8_t;
	using u16 = uint16_t;
	using u32 = uint32_t;
	using u64 = uint64_t;
	using f32 = float;
	using f64 = double;
	using size_t = std::size_t;
	using uint = unsigned int;
	using ushort = unsigned short;
}

// Logging
namespace Fluf
{
	namespace Log
	{
		enum class Category
		{
			Info,
			Warning,
			Error
		};

		constexpr int max_length = 1024;

		void info(const char* message, ...);
		void warn(const char* message, ...);
		void error(const char* message, ...);
	}
}

// Functional
#include <functional>
namespace Fluf
{
	template<class Ret, class...Args> using Func = std::function<Ret(Args...)>;
}

// Initializer list, required for Vector/StackVector
#include <initializer_list>
namespace Fluf
{
	template<typename T> using InitializerList = std::initializer_list<T>;
}

// Ref Counter, for Graphics & Input Resources
#include <memory>
namespace Fluf
{
	template<typename T> using Ref = std::shared_ptr<T>;
}