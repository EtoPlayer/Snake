#pragma once
#include <stdio.h>
#include "wall.h"

// �ߵ�ÿ�����
struct BODY
{
	int x;  // �������x����
	int y;  // �������y����
};

// �����ߵĽṹ��
struct Snake
{
	// �ߵ�һά����
	struct BODY body[(WIDTH - 2) * (HEIGHT - 2)];
	// �ߵĳ���
	int size;
}snake;  // �ߵı���

//�ߵ�ƫ����
int offset_x;
int offset_y;

//��β�±�
int tile_x;
int tile_y;

// �Ƿ�ѭ��
int isRool;

// ��ʼ����
void InitSnake();