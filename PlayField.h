#pragma once//防止头文件被重复包含
#include"Tetromino.h"
#include<string>

const int SCORE_TABLE[5] = { 0,10,30,60,100 };

class PlayField
{

public:
	static const int WIDTH = 10, T_WIDTH = WIDTH+2;
	static const int HEIGHT = 20, T_HEIGHT = HEIGHT+1;
	static const int ALIGNX_1 = 2, ALIGNX_2 = 10, ALIGNY_SCORE = 8, ALIGNY_SPEED = 14;

	using Matrix = Tetromino::Matrix;

	enum CellType
	{
		UNDEFINED,EMPTY,WALL,STATIC,DYNAMIC
	};

	PlayField();
	void fall();
	void move(int);
	void paint();
	bool failed();
	void init();
	void rotate(int);
	void fast_fall();
	int get_score();
private:
	int field[T_HEIGHT][T_WIDTH],color[T_HEIGHT][T_WIDTH], buffer[T_HEIGHT][T_WIDTH];
	int cur_block, nxt_block, rot, x, y, is_blocked, is_failed, need_flush;
	int pos;
	int score;
	std::vector<int> block_id_list;
	void elim_check();
	void clear_dynamic_block();
	bool block_check(int type,int x,int y,int rot);
	void create_new_block();
	void set_block(CellType);
};

