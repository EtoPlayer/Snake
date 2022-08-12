#pragma once
#include <stdio.h>
#include "wall.h"

// 蛇的每个身段
struct BODY
{
	int x;  // 蛇身体的x坐标
	int y;  // 蛇身体的y坐标
};

// 创建蛇的结构体
struct Snake
{
	// 蛇的一维数组
	struct BODY body[(WIDTH - 2) * (HEIGHT - 2)];
	// 蛇的长度
	int size;
}snake;  // 蛇的变量

//蛇的偏移量
int offset_x;
int offset_y;

//蛇尾下标
int tile_x;
int tile_y;

// 是否循环
int isRool;

// 初始化蛇
void InitSnake();