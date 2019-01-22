#include "pch.h"
#include "menu.h"

template <class Type>
Type setHighlightColor(Type color)
{
	menu m;
	SetConsoleTextAttribute(m.hOut, color);
	return 0;
}


menu::menu()
{
	this->margin = 0;
	this->hOut = GetStdHandle(STD_OUTPUT_HANDLE);
}

menu::menu(std::string title)
{
	this->margin = 0;
	this->title = title;
	this->hOut = GetStdHandle(STD_OUTPUT_HANDLE);
}


menu::~menu()
{
}

void menu::setOptionVector(std::vector<std::string> option)
{
	this->option = option;
}

void menu::setHL(int color)
{
	this->highlightColor = color;
}

void menu::write(int pointer, int enter)
{
	for (int i = 1; i <= option.size(); i++)
	{
		if (type == 1)
		{
			if (pointer == i)
			{
				setHighlightColor(highlightColor);
				std::cout << "[ " << std::setw(margin) << option[i - 1] << std::setw(margin) << " ]" << std::endl;
				setHighlightColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
			}
			else std::cout << "[ " << std::setw(margin) << option[i - 1] << std::setw(margin) << " ]" << std::endl;
		}
		else
		{
			if (pointer == i)
			{
				setHighlightColor(highlightColor);
				std::cout << " - " << std::setw(margin) << option[i - 1] << std::setw(margin) << " " << std::endl;
				setHighlightColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
			}
			else std::cout << " - " << std::setw(margin) << option[i - 1] << std::setw(margin) << " " << std::endl;
		}
	}
}

void menu::setPointer(int & pointer, int & enter)
{
	currentOption = pointer;
	int it = _getch();
	//std::cout << it << std::endl;
	//std::cout << option.size() << std::endl;
	if (it == 72)
	{
		if ((pointer - 1) > 0) pointer -= 1;
		else pointer = option.size();
	}
	if (it == 80)
	{
		if (pointer + 1 < option.size() + 1) pointer += 1;
		else pointer = 1;
	}
	if (it == 13) enter = 1;
}

void menu::setMargin(int margin)
{
	this->margin = margin;
}

