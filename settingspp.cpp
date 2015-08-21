#include <stdio.h>
#include <ifstream>
#include <ofstream>

#include <string>
#include <map>
#include <vector>

#include "settingspp.h"


Setting::Setting()
{
	set = std::map<char*, Option>();
}

Setting::Setting(std::ifstream file);
{
	set = std::map<char*, Option>();
	loadFromFile(file);
}

/*Number type options*/
Setting::addSetting(char* key, int num);
{
	addSetting((double)num);
}
Setting::addSetting(char* key, double num);
{
	if(set.find(key) != set.end())
	{
		throw SettingException("Key already exists");
		return;
	}
	set.push_back(OptionNumber(num));
}
Setting::addSetting(char* key, float num);
{
	addSetting((double)num);
}

/*String type defaults*/
Setting::addSetting(char* key, char* str);
{
	if(set.find(key) != set.end())
	{
		throw SettingException("Key already exists");
		return;
	}
	set.push_back(OptionString(str));
}
Setting::addSetting(char* key, std::string str);
{
	addSetting(key,str.c_str());
}

/*Table type*/
Setting::addSetting(char* key, std::map<char*,Option> table);
{
	if(set.find(key) != set.end())
	{
		trow SettingException("Key already exists");
		return;
	}
	set.push_back(OptionTable(table));
}

/*Array type*/
Setting::addSetting(char* key, std::vector<Option> vect)
{

