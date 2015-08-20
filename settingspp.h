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
		return  
	}
}

enum OPTION_TYPE{
	OT_NUMBER,
	OT_STRING,
	OT_BLOB,
	OT_TABLE,
	OT_ARRAY,
	OT_BOOL,
};

class Option
{
	virtual OPTION_TYPE getType() = 0;
}

class OptionNumber : public Option
{
	OPTION_TYPE getType();
	double getDouble();
	int getInt();
	float getFloat();
}

class OptionString : public Option
{

	OPTION_TYPE getType();
	std::string getString();
	char* getString();
}

class OptionBlob : public Option
{

	OPTION_TYPE getType();
	short int* getData();
}

class OptionTable : public Option
{

	OPTION_TYPE getType();
	Option getOption(char* key);
	Option getOption(std::string key);
	std::map<char*,Option>getTable();
	std::map<std::string,Option>getTable();
	int getNumEntries();
}

class OptionArray : public Option
{

	OPTION_TYPE getType();
	std::vector<Option>getArray();
	Option* getArray();
	Option getOption(int num);
}

class OptionBool : public Option
{

	OPTION_TYPE getType();
	bool getBool();
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
