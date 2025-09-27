#pragma once

#include <stdio.h>
#include <iostream>
#include <easyx.h>
#include <graphics.h>
#include <time.h>
#include <math.h>
#include "tools.h"


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

	int row;
	int col;

	// 匹配次数；
	bool match; 

	int tmd;


};

struct block map[ROWS + 2][COLS + 2];

const int off_x = 15;
const int off_y = 200;
const int block_size = 50;

int click;
// 第一次单击的行和列
int posX1;
int posY1;
// 第二次单击的行和列
int posX2;
int posY2;

// 是否正在移动；
bool isMoving;  

// 单击后设置为true；
bool isSwap;

int score;

void init();
void UpdateWindow();  // 更新窗口
void userClick();   // 用户点击
void move();
void huanyuan();
void static exchange(int row1, int col1, int row2, int col2);
void check();
void xiaochu();
void UpdateGame();