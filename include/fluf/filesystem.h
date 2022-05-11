#pragma once
#include <string>
#include <fstream>

namespace Fluf
{
	class File
	{
	public:
		static std::string read_file(const char* filepath)
		{
			std::ifstream ifs(filepath);
			std::string content(
				std::istreambuf_iterator<char>(ifs.rdbuf()),
				std::istreambuf_iterator<char>()
			);
			return content;
		}
	};
	
}