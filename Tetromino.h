#pragma once
#include<vector>
#include<iostream>

class Tetromino {

public:
	static const int MAX_SIZE = 4;
	static const int TYPE_NUM = 7;
	static int block_count;
	static std::vector<Tetromino*> block_list;

	using ShapeData = int[MAX_SIZE][MAX_SIZE];

	struct Matrix {
		int cell[MAX_SIZE][MAX_SIZE];
	};

	Matrix shape[4];
	int color,id;
	double dx, dy;

	Tetromino(ShapeData data[4],int color,double dx,double dy);

	static Matrix get_data(int type, int rot) {
		return block_list[type]->shape[rot];
	}

	static Tetromino* get_info(int type) {
		return block_list[type];
	}

	void paint(int x, int y, int rot);
};

extern Tetromino J_block , T_block, I_block, L_block, S_block, Z_block, O_block;