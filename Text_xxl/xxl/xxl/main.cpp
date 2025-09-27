#include "main.h"
using namespace std;

// 初始化界面
void  init()
{
	initgraph(WIN_WIDTH, WIN_HEIGHT,1);
	loadimage(&imgBg,"Photo/xxl.png");

	char name[64];
	for (int i = 0; i < BLOCK_TYPE_COUNT; i++)
	{
		sprintf_s(name, sizeof(name), "Photo/%d.png", i + 1);
		loadimage(&imgBlock[i], name, block_size, block_size, true);
	}

	// 配置随机数
	srand(time(NULL));

	for (int i = 1; i <= ROWS; i++)
	{
		for (int j = 1; j <= COLS; j++)
		{
			map[i][j].type = 1 + rand() % 5;
			map[i][j].row = i;
			map[i][j].col = j;
			map[i][j].x = off_x + (j - 1) * (block_size + 5);
			map[i][j].y = off_y + (i - 1) * (block_size + 5);
			map[i][j].match = 0;
			map[i][j].tmd = 255;
		}
	}

	click = 0;
	isMoving = false;
	isSwap = false;

}


void  UpdateWindow()
{
	BeginBatchDraw();
	putimage(0, 0, &imgBg);
	for (int i = 1; i <=ROWS; i++)
	{
		for (int j = 1; j <=COLS; j++)
		{
			if (map[i][j].type)
			{
				IMAGE* img = &imgBlock[map[i][j].type - 1];
				putimageTMD(map[i][j].x, map[i][j].y, img,map[i][j].tmd);
			}
		}
	}
	EndBatchDraw();
}

void static exchange(int row1, int col1, int row2, int col2)
{
	struct block temp = map[row1][col1];
	map[row1][col1] = map[row2][col2];
	map[row2][col2] = temp;

	map[row1][col1].row = row1;
	map[row1][col1].col = col1;
	map[row2][col2].row = row2;
	map[row2][col2].col = col2;

}


void userClick()
{
	ExMessage msg;

	if (peekmessage(&msg) && msg.message == WM_LBUTTONDOWN)
	{
		if (msg.x < off_x || msg.y < off_y) return;
		int col = (msg.x - off_x) / (block_size + 5) + 1;
		int row = (msg.y - off_y) / (block_size + 5) + 1;
		if (col > COLS || row > ROWS) return;

		click++;
		if (click == 1)
		{
			posX1 = row;
			posY1 = col;
		}

		else if (click == 2)
		{
			posX2 = row;
			posY2 = col;

			if (abs(posX2 - posX1) + abs(posY2 - posY1) == 1)
			{
				// 交换两个方块
				exchange(posX1,posY1,posX2,posY2);
				click = 0;
				isSwap = true;

				// 播放音乐
			}
			
			else
			{
				click = 1;
				posX1 = col;
				posY1 = row;
			}
		}
	}
}

void move()
{
	isMoving = false;

	for (int i = ROWS; i > 0; i--)
	{
		for (int j = 1; j <= COLS; j++)
		{
			struct block* p = &map[i][j];
			int dx, dy;

			for (int k = 0; k < 4; k++)
			{
				int x = off_x + (p->col - 1) * (block_size + 5);
				int y = off_y + (p->row - 1) * (block_size + 5);

				 dx = p->x - x;
				 dy = p->y - y;

				if (dx) p->x -= dx / abs(dx);
				if (dy) p->y -= dy / abs(dy);
			}
			
			if (dx || dy) isMoving = true;

		}
	}
}

void huanyuan()
{
	// 发生移动后 单向结束
	if (isSwap && !isMoving)
	{
		int count = 0;
		for (int i = 1; i <= ROWS; i++)
		{
			for (int j = 1; j <= COLS; j++)
			{
				count += map[i][j].match;
			}
		}

		if (count==0)
		{
			exchange(posX1, posY1, posX2, posY2);
		}

		isSwap = false;
	}
}


void check()
{
	for (int i = 1; i <= ROWS; i++)
	{
		for (int j = 1; j <= COLS; j++)
		{
			if (map[i][j].type == map[i + 1][j].type && map[i][j].type == map[i - 1][j].type)
			{
				for (int k = -1; k <= 1; k++) map[i + k][j].match++;
			}

			if (map[i][j].type == map[i][j - 1].type && map[i][j].type == map[i][j+1].type)
			{
				for (int k = -1; k <= 1; k++) map[i][j + k].match++;
			}

		}
	}
}

void xiaochu()
{
	for (int i = 1; i <= ROWS; i++)
	{
		for (int j = 1; j <= COLS; j++)
		{
			if (map[i][j].match && map[i][j].tmd > 10)
			{ map[i][j].tmd -= 3;
			isMoving = true;
			}
		}
	}
}

void UpdateGame()
{
	for (int i = ROWS; i >= 1; i--)
	{
		for (int j = 1; j <= COLS; j++)
		{
			if (map[i][j].match)
			{
				for (int k = i - 1; k >= 1; k--)
				{
					if (map[k][j].match == 0)
					{
						exchange(k, j, i, j);
						break;
					}
				}
			}
		}
	}

	for (int j = 1; j <= COLS; j++)
	{
		int n = 0;
		for (int i = ROWS; i >= 1; i--)
		{
			if (map[i][j].match)
			{
				map[i][j].type = 1 + rand() % 5;
				map[i][j].y = off_y - (n + 1) * (block_size + 5);
				n++;
				map[i][j].match = 0;
				map[i][j].tmd = 255;
			}
		}
	}
}



int main(void)
{
	init();

	while (true)
	{
		userClick();  
		check();  // 匹配检查次数
		move();

		if (!isMoving) 
		xiaochu();

		huanyuan();
		UpdateWindow();

		if (!isMoving) UpdateGame();  // 降落

		Sleep(10);

	}
	system("pause");
	return 0;
}
