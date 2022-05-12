#include <fluf/common.h>
#include <stdarg.h>
#include <stdio.h>

using namespace fluf;

void Log::info(const char* format, ...)
{
	char msg[max_length];
	va_list ap;
	va_start(ap, format);
	vsnprintf(msg, sizeof(char) * max_length, format, ap);
	va_end(ap);

	printf("%s\n", msg);
}

void Log::warn(const char* format, ...)
{
	char msg[max_length];
	va_list ap;
	va_start(ap, format);
	vsnprintf(msg, sizeof(char) * max_length, format, ap);
	va_end(ap);

	printf("WARN: %s\n", msg);
}

void Log::error(const char* format, ...)
{
	char msg[max_length];
	va_list ap;
	va_start(ap, format);
	vsnprintf(msg, sizeof(char) * max_length, format, ap);
	va_end(ap);

	printf("ERROR: %s\n", msg);
}