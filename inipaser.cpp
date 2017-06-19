#include <fstream>
#include <sstream>

#include "inipaser.h"

IniParser::IniParser(const char* filename)
{
	std::string tmp;
	std::ifstream inifile(filename, std::ios::out);

	while (std::getline(inifile, tmp))
	{
		if (tmp.find(SECTION_LEFT) == std::string::npos ||
				tmp.find(KV_SEPARATOR) == std::string::npos)
			continue;

	}
}

IniParser::~IniParser()
{

}

void IniParser::save()
{

}

void IniParser::set(const char* path, const char* value)
{

}

void IniParser::get(const char* path, char** value, std::size_t len)
{

}

std::string& IniParser::get(const char* path)
{

}

const IniParser::Section& IniParser::getSection(const char* sectionName)
{

}

