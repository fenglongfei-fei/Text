#pragma once

#include <stdio.h>
#include <iostream>
#include <easyx.h>
#include <graphics.h>
#include <time.h>
#include "tools.h"
using namespace std;

#define WIN_WIDTH 474
#define WIN_HEIGHT 899
#define ROWS 8
#define COLS 8
#define BLOCK_TYPE_COUNT 7

IMAGE imgBg;   // 表示图片
IMAGE imgBlock[BLOCK_TYPE_COUNT];

struct block
{
	int type;
	int x;
	int y;
	int row, col;
};

struct block map[ROWS + 2][COLS + 2];

const int off_x = 20;
const int off_y = 250;
const int block_size = 55;


void init();
void UpdateWindow();  // 更新窗口
void userClick();   // 用户点击
void move();
void huanyuan();