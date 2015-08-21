#include <string>
#include <fstream>
#include <map>
#include <vector>

#include <iterator>
#include <typeinfo>
#include <excpetion>

class SettingException : public exception
{
	bool lastinfo;
	private long int lastlinenum;
	private char* lastlinestring;
	private char* information;	
	SettingException();
	SettingException(char* str);
	SettingException(int num, char* str)
	SettingException(int num, char* lastline, char* information);	
	const char* what() const throw();
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

	public
	{
		virtual OPTION_TYPE getType() = 0;
	}

}

class OptionNumber : public Option
{
	public
	{
		OptionNumber(double);
		OptionNumber(int);
		OptionNumber(float);

		OPTION_TYPE getType();
		double getDouble();
		int getInt();
		float getFloat();
	}
}

class OptionString : public Option
{
	private
	{
		char* string;
	}

	public
	{
		OptionString();
		OptionString(char* str);
		OptionString(std::string str);
		OPTION_TYPE getType();
		std::string getString();
		char* getString();
	}
}

class OptionBlob : public Option
{
	public
	{
		OPTION_TYPE getType();
		short int* getData();

	}
}

class OptionTable : public Option
{
	private
	{
		std::map<char*,Option> optab;
	}


	public
	{
		OptionTable(std::map<char*, Option> table);
		OptionTable();
		OPTION_TYPE getType();
		Option getOption(char* key);
		Option getOption(std::string key);
		std::map<char*,Option>getTable();
		int getNumEntries();
	}
}

class OptionArray : public Option
{
	private
	{
		std::vector<Option> optvec;
	}
	public
	{
		OptionArray(std::vector<Option> vect);
		OptionArray();
		OPTION_TYPE getType();
		std::vector<Option>getArray();
		Option* getArray();
		Option getOption(int num);

	}
}

class OptionBool : public Option
{
	public
	{
		OPTION_TYPE getType();
		bool getBool();
	}
}

class Setting
{
	private
	{

		std::map<char*,Option> set;
	}

	public
	{

		//Setting::addSetting(char* key); //Option with a blank default

		Setting();
		Setting(std::ifstream file);

		/*Number type defaults*/
		void Setting::addSetting(char* key,int num);
		Setting::addSetting(char* key,double num);
		Setting::addSetting(char* key,float num);

		/*String type defaults*/
		void Setting::addSetting(char* key,char* str);
		void Setting::addSetting(char* key,std::string str);

		/*Data blob type*/
		//void Setting::addSetting(char* key,void* blob);

		/*Table type*/
		void Setting::addSetting(char* key,std::map<char*, Option> table);
	
		/*Array type*/
		void Setting::addSetting(char* key,std::vector<Option> vect);
	
		/*Boolean type*/
		void Setting::addSetting(char* key,bool val);

		/*Retreive a value*/
		Option Setting::getSetting(char* key);
		template<class T>
		T Setting::getSetting(char* key);

		/*Save to a file*/
		void Setting::saveToFile(std::ofstream file);
		void Setting::saveToFile(std::ofstream file, bool overwirte = false);
	
		/*Load settings from a file*/
		void Setting::loadFromFile(std::ifstream file); 

	}
	
}
