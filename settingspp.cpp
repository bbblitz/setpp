#include <stdio.h>
#include <fstream>
#include <string>
#include <map>
#include <vector>

#include "settingspp.h"

/*
 * Exceptions to throw:
 * 	Key already exists
 * 	Key dosen't exist
 * 	No file permissions
 * 	File does not exist
 * 	Failed to open
 * 	Failed to parse file
 * 	EOF not expected
 */
void throwKeyAlreadyExistsException(std::string key)
{
	throw SettingException("Key already exists: " + key);
}

void throwKeyDosntExistExcpetion(std::string key)
{
	throw SettingException("Key does not exist: " + key);
}

void throwFilePermissionDeniedException(std::string filename)
{
	throw SettingException("File permission denied: " + filename);
}

void throwFileDoesNotExistException(std::string filepath)
{
	throw SettingException("File does not exist: " filepath);
}

void throwFileFailedToOpenException(std::string filepath)
{
	throw SettingExcpetion("Failed to open: " + filepath);
}

void throwFailedToParseFileException(std::string filepath, int line, std::string str)
{
	throw SettingException("Failed to parse \"" + filepath + "\" at line " + itoa(line) + ", " + std::endl + str);
}

void throwEOFNotExpectedException()
{
	throw SettingException("End of file not expected");
}

/*Settings class*/
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
		throwKeyAlreadyExistsException(std::string(key));
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
		throwKeyAlreadyExistsException(std::string(key));
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
		throwKeyAlreadyExistsException(std::string(key));
	}
	set.push_back(OptionTable(table));
}

	/*Array type*/
Setting::addSetting(char* key, std::vector<Option> vect)
{
	if(set.find(key) != set.end())
	{
		throwKeyAlreadyExistsException(std::string(key));
	}
	set.push_back(OptionTable(table));
}

	/*Boolean type*/
Setting::addSetting(char* key, bool val)
{
	if(set.find(key) != set.end())
	{
		throwKeyAlreadyExistsException(std::string(key));
	}
	set.push_back(OptionBool(table));
}

	/*Retreive a value*/
Option Setting::getSetting(char* key)
{
	if(set.find(key) == set.end())
	{
		throwKeyDosntExistException(std::string(key));	
	}
	return set[key];
}

/*Class OptionNumber*/
OptionNumber::OptionNumber(double n)
{
	num = n;
}
OptionNumber::OptionNumber(int n)
{
	num = (double)n;
}
OptionNumber::OptionNumber(float n)
{
	num = (double)n;
}

