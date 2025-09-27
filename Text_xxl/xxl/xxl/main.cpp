#include "main.h"


void  init()
{
	initgraph(WIN_WIDTH, WIN_HEIGHT);
	loadimage(&imgBg,"Photo/xxl.png");

	char name[64];
	for (int i = 0; i < BLOCK_TYPE_COUNT; i++)
	{
		sprintf_s(name, sizeof(name), "Photo/%d.png", i + 1);
		loadimage(&imgBlock[i], name, block_size, block_size, true);
	}

	// ÅäÖÃËæ»úÊý
	srand(time(NULL));

	for (int i = 1; i <= ROWS; i++)
	{
		for (int j = 1; j < COLS; j++)
		{
			map[i][j].type = 1+rand() % 4;
			map[i][j].row = i;
			map[i][j].col = j;
			map[i][j].x = off_x + (j - 1) * (block_size + 5);
			map[i][j].y = off_y + (i - 1) * (block_size + 5);
		}
	}
}

void  UpdateWindow()
{
	putimage(0, 0, &imgBg);
	for (int i = 1; i <=ROWS; i++)
	{
		for (int j = 1; j <=COLS; j++)
		{
			if (map[i][j].type)
			{
				IMAGE* img = &imgBlock[map[i][j].type - 1];
				putimagePNG(map[i][j].x, map[i][j].y, img);
			}
		}
	}
}

void userClick()
{
	ExMessage msg;
	if (peekmessage(&msg) && msg.message == WM_LBUTTONDOWN)
	{

	}

}

void move()
{

}

void huanyuan()
{

}


int main(void)
{
	init();

	while (true)
	{
		userClick();
		move();
		huanyuan();
		UpdateWindow();

		Sleep(10);

	}
	system("pause");
	return 0;
}
