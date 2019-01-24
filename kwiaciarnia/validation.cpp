#include "pch.h"
#include "validation.h"


validation::validation()
{
}


validation::~validation()
{
}


int validation::isPost(std::string post)
{
	std::regex p("^[0-9]{2}-[0-9]{3}$");
	if (std::regex_match(post, p)) return 0;
	else return 1;
}

int validation::isAppropriateLength(std::string str, int minLength, int maxLength)
{
	if (str.length() > minLength)
	{
		if (str.length() < maxLength) return 0;
		else return 2;
	}
	else return 1;
}

bool validation::isDate(std::string date)
{
	std::regex p("^[0-9]{4}-[0-9]{2}-[0-9]{2}$");
	if (std::regex_match(date, p)) return 0;
	else return 1;
}


std::string validation::returnDayName(int date)
{
	switch (date)
	{
	case 1: return "PON"; break;
	case 2: return "WTO"; break;
	case 3: return "SRO"; break;
	case 4: return "CZW"; break;
	case 5: return "PIA"; break;
	case 6: return "SOB"; break;
	case 7: return "NIE"; break;
	}
	return 0;
}

int validation::conv(std::string a) {
	int v = 0;
	for (int b = 0; b < a.length(); b++) v = v * 10 + a[b] - 48;

	return v;
}
bool validation::isnum(std::string t) {
	for (int a = 0; a < t.length(); a++) {
		if (t[a] > '0' + 9 || t[a] < '0') return false;

	}
	return true;
}