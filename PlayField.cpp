#include "PlayField.h"
#include "Tetromino.h"

#include <cstdlib>
#include <string>
#include <iostream>
#include <Windows.h>
#include <algorithm>
#include "painter.h"

int PlayField::get_score() {
	return score;
}

PlayField::PlayField() {
	for (int i = 0; i < T_HEIGHT; ++i)
		for (int j = 0; j < T_WIDTH; ++j) {
			field[i][j] = EMPTY;
			buffer[i][j] = -1;
			color[i][j] = BLACK;
		}
	for (int i = 1; i <= WIDTH; ++i)
		field[HEIGHT][i] = WALL,
		color[HEIGHT][i] = GRAY;
	for (int i = 0; i <= HEIGHT; ++i)
		field[i][0] = field[i][WIDTH + 1] = WALL,
		color[i][0] = color[i][WIDTH + 1] = GRAY;
	score = 0;
	is_failed = false;
	is_blocked = false;
	need_flush = true;
	pos=rot = x = y = cur_block = nxt_block = -1;
}

void PlayField::elim_check() {
	int cnt = 0,las=HEIGHT-1;
	for (int i = HEIGHT-1; i >= 0; --i) {
		int num = 0;
		for (int j = 1; j <= WIDTH; ++j)
			num += field[i][j] != EMPTY;
		if (num == WIDTH) {
			cnt++;
			for (int j = 1; j <= WIDTH; ++j)
				field[i][j] = EMPTY,
				color[i][j] = BLACK;
		}
		else {
			for (int j = 1; j <= WIDTH; ++j)
				field[las][j] = field[i][j],
				color[las][j] = color[i][j];
			las--;
		}
	}
	score += SCORE_TABLE[cnt];
}

bool PlayField::block_check(int type, int x, int y, int rot) {
	Matrix block = Tetromino::get_data(type, rot);
	for(int i=0;i<Tetromino::MAX_SIZE;++i)
		for (int j = 0; j < Tetromino::MAX_SIZE; ++j)
			if(block.cell[i][j]) {
				if (field[i + x][j + y] != EMPTY) {
					//DEBUG("failed at "+std::to_string(i+x)+","+std::to_string(i+y));
					return true;
				}
			}
	return false;
}

void PlayField::paint() {
	set_block(DYNAMIC);
	for(int i=0;i<T_HEIGHT;++i)
		for(int j=0;j<T_WIDTH;++j)
			if (buffer[i][j] != color[i][j]) {
				paint_at(j,i,color[i][j], "  ");
				buffer[i][j] = color[i][j];
			}
	if(need_flush){
		for (int i = 0; i < T_HEIGHT; ++i) {
			paint_at(T_WIDTH + ALIGNX_1, i, NORMAL, "||");
			paint_at(T_WIDTH + ALIGNX_2, i, NORMAL, "||");
		}
		double center_align = T_WIDTH + (ALIGNX_1 + ALIGNX_2) / 2.0 + 0.5;
		paint_at_center(center_align,0,NORMAL,"NEXT");
		Tetromino::get_info(nxt_block)->paint(2,T_WIDTH+ALIGNX_1+3,0);
		paint_at_center(center_align, ALIGNY_SCORE, NORMAL, "SCORE");
		paint_at_center(center_align, ALIGNY_SCORE + 2, NORMAL, "            ");
		paint_at_center(center_align, ALIGNY_SCORE+2, NORMAL, std::to_string(score));
		paint_at_center(center_align, ALIGNY_SPEED, NORMAL, "SPEED");
		paint_at_center(center_align, ALIGNY_SPEED + 2, NORMAL, "            ");
		paint_at_center(center_align, ALIGNY_SPEED + 2, NORMAL, std::to_string(3+score/400));
		need_flush = false;
	}
	SetConsoleCursorPosition(GetStdHandle((DWORD)-11), { 0,23 });
	clear_dynamic_block();
}

void PlayField::fall() {
	if (failed())return;
	if (block_check(cur_block, x + 1, y, rot)) {
		//DEBUG("fail at"+std::to_string(x+1)+","+std::to_string(y));
		if (is_blocked) {
			set_block(STATIC);
			create_new_block();
			is_blocked = false;
			need_flush = true;
		}
		else is_blocked = true;
	}
	else {
		x++;
	}
	paint();
}

void PlayField::create_new_block() {
	int block_num = Tetromino::block_count;
	if (pos == -1) {
		pos = 0;
		std::random_shuffle(block_id_list.begin(), block_id_list.end());
		nxt_block = block_id_list[0];
	}
	cur_block = nxt_block;
	++pos;
	if (pos >= block_num) {
		pos = 0;
		std::random_shuffle(block_id_list.begin(), block_id_list.end());
	}
	nxt_block = block_id_list[pos];
	x = 0;
	y = rand() % 4 + 4;
	rot = rand() % 4;
	if (block_check(cur_block, x, y, rot)) {
		DEBUG("FAILED");
		is_failed = true;
		set_block(STATIC);
	}
}

bool PlayField::failed() {
	return is_failed;
}

void PlayField::set_block(CellType type) {
	Matrix block = Tetromino::get_data(cur_block, rot);
	Tetromino* cur = Tetromino::get_info(cur_block);
	for (int i = 0; i < Tetromino::MAX_SIZE; ++i)
		for (int j = 0; j < Tetromino::MAX_SIZE; ++j)
			if (block.cell[i][j]) {
				if (field[i+x][j+y] != EMPTY)
					continue;
				field[i+x][j+y] = type;
				color[i+x][j+y] = cur->color;
			}
	if (type==STATIC&&!failed())
		elim_check();
}

void PlayField::move(int dy) {
	if (block_check(cur_block, x, y + dy, rot))
		return;
	y += dy;
	paint();
}

void PlayField::rotate(int d) {
	int nd = (rot + d + 4) % 4;
	if (block_check(cur_block, x, y, nd))
		return;
	rot = nd;
	is_blocked = false;
	paint();
}

void PlayField::init() {
	for (int i = 0; i < Tetromino::block_count; ++i)
		block_id_list.push_back(i);
	pos = -1;
	create_new_block();
	paint();
}

void PlayField::clear_dynamic_block() {
	for (int i = 0; i <= HEIGHT; ++i)
		for (int j = 1; j <= WIDTH; ++j)
			if (field[i][j] == DYNAMIC) {
				field[i][j] = EMPTY;
				color[i][j] = BLACK;
			}
}

void PlayField::fast_fall() {
	while (!block_check(cur_block, x + 1, y, rot)) {
		x++;
	}
	is_blocked = true;
	paint();
}