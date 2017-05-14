#include "stdafx.h"
#include "File.h"

std::string File::ReadToEnd(std::string path)
{
	std::ifstream file(path, std::ios::in);
	if (file)
	{
		//чтение файла
		std::string contents;
		file.seekg(0, std::ios::end);
		contents.resize(file.tellg());
		file.seekg(0, std::ios::beg);
		file.read(&contents[0], contents.size());
		file.close();
		return contents;
	}throw errno;
}
