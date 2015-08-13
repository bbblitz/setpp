#include <string>
#include <fstream>
#include <map>
#include <vector>

#include <typeinfo>
#include <excpetion>

class SettingException : public exception
{
	private long int lastlinenum;
	private char* lastlinestring;
	
	SettingException()
	SettingException(int num, char* str)
	{
		lastlinenum = num;
		lastlinestring = str;
	}	
	
	virtual const char* what() const throw()
	{
		return sprintf("Failed to parse settings near line %d, %s",lastlinenum,lastlinestring);
	}
}

class Option
{

}

class OptionNumber : public Option
{

}

class OptionString : public Option
{

}

class OptionBlob : public Option
{

}

class OptionTable : public Option
{

}

class OptionArray : public Option
{

}

class OptionBool : public Option
{

}

class Setting
{
	private{

		std::map<char*,Option> set;
	}

	public{

		Setting::addSetting(char* key); //Option with a blank default

		/*Number type defaults*/
		void Setting::addSetting(char* key,int num);
		Setting::addSetting(char* key,double num);
		Setting::addSetting(char* key,float num);

		/*String type defaults*/
		void Setting::addSetting(char* key,char* str);
		void Setting::addSetting(char* key,std::string str);

		/*Data blob type*/
		void Setting::addSetting(char* key,void* blob);

		/*Table type*/
		void Setting::addSetting(char* key,std::map table);
	
		/*Array type*/
		void Setting::addSetting(char* key,std::vector vect);
	
		/*Boolean type*/
		void Setting::addSetting(char* key,bool val);

		/*Retreive a value*/
		Option Setting::getSetting(char* key);
		template<class T>
		T Setting::getSetting(char* key);

		/*Save to a file*/
		void Setting::saveToFile(std::ofstream file);
	
		/*Load settings from a file*/
		void Setting::loadFromFile(std::ifstream file, bool overwrite = true);

	}
	
}
