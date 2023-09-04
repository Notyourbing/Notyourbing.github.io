#include "painter.h"
#include <Windows.h>
#include <iostream>

void paint_at(double x, int y, int color, std::string s)//在控制台窗口的指定位置以指定的颜色绘制字符串s
{
	SetConsoleTextAttribute(GetStdHandle((DWORD)-11), color);
	COORD coord = { x * 2,y };
	SetConsoleCursorPosition(GetStdHandle((DWORD)-11), coord);
	std::cout << s;
}

void paint_at_center(double x, int y, int color, std::string s) //绘制在中心位置 
{
	SetConsoleTextAttribute(GetStdHandle((DWORD)-11), color);
	COORD coord = { x * 2 - s.length()/2,y };
	SetConsoleCursorPosition(GetStdHandle((DWORD)-11), coord);
	std::cout << s;
	SetConsoleCursorPosition(GetStdHandle((DWORD)-11), {0,23});
}

void DEBUG(std::string s) //调试消息
{
	SetConsoleCursorPosition(GetStdHandle((DWORD)-11), { 0,22 });
	std::cout << s << std::endl;
}