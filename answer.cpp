#include<iostream>
#include<ctime>
#include<iomanip>
#include<conio.h>
#include <stdlib.h>

//游戏的行列格数（超过10时需要修改位置读取函数
#define COL 4
#define ROW 4
//新出现的数字为2的比例
#define RATIO 0.9
int real_time_mark;//即时总分
int best_score = 0;//最佳分数
bool ifPlaying = true;//记录游戏是否正在进行

					  //定义一个函数和用来打印表格
void printMe(int table[ROW][COL])
{
	system("cls");
	printf("\n\n           Game:2048                SCORE:%6d             BEST:%6d\n", real_time_mark, best_score);
	printf("----------------------------------------------------------------------------------------\n\n\n");
	printf("\n                   -----------------------------------------\n");
	for (int n = 0; n < ROW; n++)
	{
		printf("                   |");
		for (int m = 0; m < COL; m++)
		{
			if (table[n][m] == 0) {
				printf("         |");
			}
			else {
				//按从上至下的顺序打印二维数组
				printf("%8d |", table[n][m]);
			}
			
			if (m == COL - 1)
				printf("\n                   -----------------------------------------\n");
		}
	}
	printf("\n\n----------------------------------------------------------------------------------------\n\n\n");
	printf("Press Q to quit.");
}

//检查是否已经无法移动，游戏结束
bool gameOverCheck(int table[ROW][COL])
{
	bool ifFull = true;
	for (int m = 0; m < ROW; m++)
	{
		for (int n = 0; n < COL; n++)
		{
			if (table[m][n] == 0)
			{
				ifFull = false;
			}
		}
	}
	if (ifFull) {
		bool ifCannotMove = true;
		for (int m = 0; m < ROW; m++)
		{
			for (int n = 0; n < COL - 1; n++)
			{
				if (table[m][n] == table[m][n + 1])
				{
					ifCannotMove = false;
				}
			}
		}
		for (int n = 0; n < COL; n++)
		{
			for (int m = 0; m < ROW - 1; m++)
			{
				if (table[m][n] == table[m + 1][n])
				{
					ifCannotMove = false;
				}
			}
		}
		if (ifCannotMove)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

//游戏结束界面
void printGameOver()
{
	ifPlaying = false;
	system("cls");
	printf("\n\n\n              Game    Over   !!!\n\n\n              Your Score:%d\n\n\n              press r to restart, press any other button to exit  !!!", real_time_mark);
	if (best_score < real_time_mark)
	{
		best_score = real_time_mark;
		printf("\n\n\n              You had broke the record      !!!\n\n\n              Congratulations!!!");
	}
}

//控制分数增加，每一次得分时调用
void addToMark(int addition)
{
	real_time_mark += addition;
}

//规定新出现的数字的大小
int createNewNum()
{
	if (rand() / (RAND_MAX + 1.0) < RATIO)
	{
		return 2;
	}
	else
	{
		return 4;
	}
}

//确定新出现数字的位置
int locateNewNum(int table[ROW][COL])
{
	while (true) {
		for (int n = 0; n < ROW; n++)
		{
			if (rand() / (RAND_MAX + 1.0) > 0.8)
			{
				for (int m = 0; m < COL; m++)
				{
					if (table[n][m] == 0)
					{
						if (rand() / (RAND_MAX + 1.0) > 0.8)
						{
							return (n * 10 + m);
						}
					}
				}
			}
		}
	}
}

//解码字符中储存的位置的X坐标
int getNewNumX(int code)
{
	return code / 10;
}

//解码字符中储存的位置的Y坐标
int getNewNumY(int code)
{
	return (code - (code / 10) * 10);
}

//接受到上键时的操作
void whenUp(int table[ROW][COL])
{
	bool ifMove = false;
	//循环处理格网中的每一列
	for (int n = 0; n < COL; n++)
	{
		int temp = 0;
		//存放更新后的某列
		int newCol[ROW] = { 0 };
		int count = 0;
		//循环处理列中每一个数
		for (int m = 0; m < ROW; m++)
		{
			if (table[m][n] != 0)
			{
				if (temp != 0 && temp == table[m][n]) {
					newCol[count - 1] = 2 * temp;
					addToMark(2 * temp);
					temp = 0;
					ifMove = true;
				}
				else
				{
					temp = table[m][n];
					newCol[count] = temp;
					if (m != count) {
						ifMove = true;
					}
					count++;
				}
			}
		}
		for (int m = 0; m < ROW; m++)
		{
			table[m][n] = newCol[m];
		}
	}
	if (ifMove) {
		char location = locateNewNum(table);
		table[getNewNumX(location)][getNewNumY(location)] = createNewNum();
		printMe(table);
		if (gameOverCheck(table))
		{
			printGameOver();
		}
	}
}

//接受到下键的操作
void whenDown(int table[ROW][COL])
{
	bool ifMove = false;
	for (int n = 0; n < COL; n++)
	{
		int temp = 0;
		//存放更新后的某列
		int newCol[ROW] = { 0 };
		int count = 0;
		//将该列倒序
		int adverseCol[ROW] = { 0 };
		for (int m = 0; m < ROW; m++) {
			adverseCol[ROW - 1 - m] = table[m][n];
		}
		//处理该列中的每一个数
		for (int m = 0; m < ROW; m++)
		{
			if (adverseCol[m] != 0)
			{
				if (temp != 0 && temp == adverseCol[m])
				{
					newCol[count - 1] = 2 * temp;
					addToMark(2 * temp);
					temp = 0;
					ifMove = true;
				}
				else
				{
					temp = adverseCol[m];
					newCol[count] = temp;
					if (m != count) {
						ifMove = true;
					}
					count++;
				}

			}
		}
		for (int m = 0; m < ROW; m++)
		{
			table[ROW - 1 - m][n] = newCol[m];
		}
	}
	if (ifMove) {
		char location = locateNewNum(table);
		table[getNewNumX(location)][getNewNumY(location)] = createNewNum();
		printMe(table);
		if (gameOverCheck(table))
		{
			printGameOver();
		}
	}
}

//接受到右键的操作
void whenRight(int table[ROW][COL])
{
	bool ifMove = false;
	//循环处理个网中的每一行
	for (int m = 0; m < ROW; m++)
	{
		int temp = 0;
		int newRow[COL] = { 0 };
		int count = 0;
		//将该行倒序
		int adverseRow[COL] = { 0 };
		for (int n = 0; n < COL; n++)
		{
			adverseRow[COL - 1 - n] = table[m][n];
		}
		//循环处理行中的每一个数
		for (int n = 0; n < COL; n++)
		{
			if (adverseRow[n] != 0)
			{
				if (temp != 0 && temp == adverseRow[n])
				{
					newRow[count - 1] = 2 * temp;
					addToMark(2 * temp);
					temp = 0;
					ifMove = true;
				}
				else
				{
					temp = adverseRow[n];
					newRow[count] = temp;
					if (n != count) {
						ifMove = true;
					}
					count++;
				}
			}
		}
		for (int n = 0; n < COL; n++)
		{
			table[m][COL - 1 - n] = newRow[n];
		}
	}
	if (ifMove) {
		char location = locateNewNum(table);
		table[getNewNumX(location)][getNewNumY(location)] = createNewNum();
		printMe(table);
		if (gameOverCheck(table))
		{
			printGameOver();
		}
	}
}

//接受到左键时的操作
void whenLeft(int table[ROW][COL])
{
	bool ifMove = false;
	//循环处理个网中的每一行
	for (int m = 0; m < ROW; m++)
	{
		int temp = 0;
		int newRow[COL] = { 0 };
		int count = 0;
		//循环处理行中的每一个数
		for (int n = 0; n < COL; n++)
		{
			if (table[m][n] != 0)
			{
				if (temp != 0 && temp == table[m][n]) {
					newRow[count - 1] = 2 * temp;
					addToMark(2 * temp);
					temp = 0;
					ifMove = true;
				}
				else
				{
					temp = table[m][n];
					newRow[count] = temp;
					if (n != count) {
						ifMove = true;
					}
					count++;
				}
			}
		}
		for (int n = 0; n < COL; n++)
		{
			table[m][n] = newRow[n];
		}
	}
	if (ifMove) {
		char location = locateNewNum(table);
		table[getNewNumX(location)][getNewNumY(location)] = createNewNum();
		printMe(table);
		if (gameOverCheck(table))
		{
			printGameOver();
		}
	}
}

void setOriginalLocation(int table[ROW][COL])
{
	int x = (int)(floor((rand() / (RAND_MAX + 1.0)) * COL));
	int y = (int)(floor((rand() / (RAND_MAX + 1.0)) * ROW));
	table[x][y] = 2;
}

void initializeGame(int table[ROW][COL])
{
	for (int n = 0; n < ROW; n++)
		for (int m = 0; m < COL; m++)
			table[n][m] = 0;
	real_time_mark = 0;
	setOriginalLocation(table);
	printMe(table);
}

int main()
{
	int gameTable[ROW][COL] = { 0 };
	initializeGame(gameTable);
	bool ifExit = false;
	while (!ifExit)
	{
		switch (_getch())
		{
		case 75:
			whenLeft(gameTable);
			break;
		case 80:
			whenDown(gameTable);
			break;
		case 77:
			whenRight(gameTable);
			break;
		case 72:
			whenUp(gameTable);
			break;
		case 'Q':
			ifExit = true;
			break;
		default:
			break;
		}
		if (!ifPlaying) {
			switch (_getch())
			{
			case 'r':
				ifPlaying = true;
				initializeGame(gameTable);
				break;
			default:
				ifExit = true;
			}
		}
	}
	return 0;
}
