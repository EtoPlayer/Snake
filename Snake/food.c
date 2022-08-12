#include "food.h"

void InitFood()
{
	int flag = 0;

	while (1) {
		//初始化食物的坐标
		food.x = rand() % (WIDTH - 2) + 1;
		food.y = rand() % (HEIGHT - 2) + 1;

		//检查食物是否与蛇重叠
		for (int i = 0; i < snake.size; i++) {
			if (snake.body[i].x == food.x && snake.body[i].y == food.y) {
				flag = 1;
				break;
			}
		}

		//食物不与蛇重叠，退出循环
		if (flag == 0) {
			break;
		}
	}
}
