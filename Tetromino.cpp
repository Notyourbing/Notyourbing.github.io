#include "Tetromino.h"
#include "painter.h"
#include <cstring>

int Tetromino::block_count = 0;
std::vector<Tetromino*> Tetromino::block_list;

Tetromino::Tetromino(ShapeData data[4], int color = 0x60, double dx = 0, double dy = 0) :
	color(color), dx(dx), dy(dy) {
	id = Tetromino::block_count++;
	for (int i = 0; i < 4; ++i)
		memcpy(shape[i].cell, data[i], sizeof(data[i]));
	Tetromino::block_list.push_back(this);
}

void Tetromino::paint(int x, int y, int rot) {
	for (int i = -1; i < MAX_SIZE; ++i)
		for (int j = -1; j < MAX_SIZE; ++j)
			paint_at(y + j, x + i, NORMAL, "  ");
	for (int i = 0; i < MAX_SIZE; ++i)
		for (int j = 0; j < MAX_SIZE; ++j)
			if (shape[rot].cell[i][j])
				paint_at(y + j+dy, x + i+dx, color, "  ");
}

static Tetromino::ShapeData T_data[4] = {
	{{0,1,0},
	 {1,1,1},
	 {0,0,0},
	 {}},
	{{0,1,0},
	 {0,1,1},
	 {0,1,0},
	 {}},
	{{0,0,0},
	 {1,1,1},
	 {0,1,0},
	 {}},
	{{0,1,0},
	 {1,1,0},
	 {0,1,0},
	 {}}
};

static Tetromino::ShapeData L_data[4] = {
	{{0,0,1},
	 {1,1,1},
	 {0,0,0},
	 {}},
	{{0,1,0},
	 {0,1,0},
	 {0,1,1},
	 {}},
	{{0,0,0},
	 {1,1,1},
	 {1,0,0},
	 {}},
	{{1,1,0},
	 {0,1,0},
	 {0,1,0},
	 {}}
};

static Tetromino::ShapeData J_data[4] = {
	{{0,0,0},
	 {1,1,1},
	 {0,0,1},
	 {}},
	{{0,1,0},
	 {0,1,0},
	 {1,1,0},
	 {}},
	{{1,0,0},
	 {1,1,1},
	 {0,0,0},
	 {}},
	{{0,1,1},
	 {0,1,0},
	 {0,1,0},
	 {}}
};

static Tetromino::ShapeData S_data[4] = {
	{{0,1,1},
	 {1,1,0},
	 {0,0,0},
	 {}},
	{{0,1,0},
	 {0,1,1},
	 {0,0,1},
	 {}},
	{{0,1,1},
	 {1,1,0},
	 {0,0,0},
	 {}},
	{{0,1,0},
	 {0,1,1},
	 {0,0,1},
	 {}}
};

static Tetromino::ShapeData Z_data[4] = {
	{{1,1,0},
	 {0,1,1},
	 {0,0,0},
	 {}},
	{{0,0,1},
	 {0,1,1},
	 {0,1,0},
	 {}},
	{{0,0,0},
	 {1,1,0},
	 {0,1,1},
	 {}},
	{{0,1,0},
	 {1,1,0},
	 {1,0,0},
	 {}}
};

static Tetromino::ShapeData O_data[4] = {
	{{1,1},
	 {1,1},
	 {},
	 {}},
	{{1,1},
	 {1,1},
	 {},
	 {}},
	{{1,1},
	 {1,1},
	 {},
	 {}},
	{{1,1},
	 {1,1},
	 {},
	 {}}
};

static Tetromino::ShapeData I_data[4] = {
	{{},
	 {1,1,1,1},
	 {},
	 {}},
	{{0,0,1},
	 {0,0,1},
	 {0,0,1},
	 {0,0,1}},
	{{},
	 {1,1,1,1},
	 {},
	 {}},
	{{0,1},
	 {0,1},
	 {0,1},
	 {0,1}}
};

Tetromino J_block(J_data,0x10,-1);
Tetromino T_block(T_data,0xd0);
Tetromino I_block(I_data,0x90,-1,-0.5);
Tetromino L_block(L_data,0xc0);
Tetromino S_block(S_data,0xa0);
Tetromino Z_block(Z_data,0x40);
Tetromino O_block(O_data,0x60,0,0.5);