#pragma once
#include <string>
#include <vector>
#include <iomanip>
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <conio.h>
class menu
{
public:
	HANDLE hOut;
	std::string title;
	std::vector<std::string> option;
	int currentOption;
	int highlightColor;
	int margin;
	int type;
	menu();
	menu(std::string title);
	~menu();
	void setOptionVector(std::vector<std::string> option);
	void setHL(int color);
	void write(int pointer, int enter);
	void setPointer(int &pointer, int &enter);
	void setMargin(int margin);
};

