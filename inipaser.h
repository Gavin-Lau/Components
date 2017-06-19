#ifndef _INIPARSER_H_
#define _INIPARSER_H_

#include <iostream>
#include <vector>
#include <map>

#define SECTION_LEFT	'['
#define SECTION_RIGHT	']'
#define KV_SEPARATOR	'='

class IniParser {

public:

	typedef std::vector<std::pair<std::string, std::string> > Section;


	IniParser(const char* filename);
	~IniParser();
	void save();
	void set(const char* path, const char* value);
	void get(const char* path, char** value, std::size_t len);
	std::string& get(const char* path);
	const Section& getSection(const char* sectionName);

private:

	
	typedef std::vector<std::pair<std::string, Section*> > iroot;
	iroot	m_iniroot;
};

#endif //_INIPARSER_H_