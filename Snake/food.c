#include "food.h"

void InitFood()
{
	int flag = 0;

	while (1) {
		//��ʼ��ʳ�������
		food.x = rand() % (WIDTH - 2) + 1;
		food.y = rand() % (HEIGHT - 2) + 1;

		//���ʳ���Ƿ������ص�
		for (int i = 0; i < snake.size; i++) {
			if (snake.body[i].x == food.x && snake.body[i].y == food.y) {
				flag = 1;
				break;
			}
		}

		//ʳ�ﲻ�����ص����˳�ѭ��
		if (flag == 0) {
			break;
		}
	}
}
