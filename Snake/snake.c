#include "snake.h"

// ��ʼ����
void InitSnake()
{
	// �ߵĴ�С
	snake.size = 3;

	// �ߵ�����
	snake.body[0].x = WIDTH / 2;
	snake.body[0].y = HEIGHT / 2;

	snake.body[1].x = WIDTH / 2 - 1;
	snake.body[1].y = HEIGHT / 2;

	snake.body[2].x = WIDTH / 2 - 2;
	snake.body[2].y = HEIGHT / 2;
}