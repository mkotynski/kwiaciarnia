#pragma once
#include <string>
#include <iostream>
#include <regex>

class validation
{
public:
	validation();
	~validation();
	static int isPost(std::string post);
	static int isAppropriateLength(std::string str, int minLength, int maxLength);
	static bool isDate(std::string date);
	static std::string returnDayName(int date);
};

