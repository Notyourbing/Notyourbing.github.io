#include "painter.h"
#include <Windows.h>
#include <iostream>

void paint_at(double x, int y, int color, std::string s)//�ڿ���̨���ڵ�ָ��λ����ָ������ɫ�����ַ���s
{
	SetConsoleTextAttribute(GetStdHandle((DWORD)-11), color);
	COORD coord = { x * 2,y };
	SetConsoleCursorPosition(GetStdHandle((DWORD)-11), coord);
	std::cout << s;
}

void paint_at_center(double x, int y, int color, std::string s) //����������λ�� 
{
	SetConsoleTextAttribute(GetStdHandle((DWORD)-11), color);
	COORD coord = { x * 2 - s.length()/2,y };
	SetConsoleCursorPosition(GetStdHandle((DWORD)-11), coord);
	std::cout << s;
	SetConsoleCursorPosition(GetStdHandle((DWORD)-11), {0,23});
}

void DEBUG(std::string s) //������Ϣ
{
	SetConsoleCursorPosition(GetStdHandle((DWORD)-11), { 0,22 });
	std::cout << s << std::endl;
}