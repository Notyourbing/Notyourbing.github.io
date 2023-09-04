#pragma once
#include<string>

const int GRAY = 0x80, BLACK = 0x00, NORMAL = 0x07;

void paint_at(double x, int y, int color, std::string s);
void paint_at_center(double x, int y, int color, std::string s);
void DEBUG(std::string s);