#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "food.h"
#include "snake.h"
#include "wall.h"
#include "windows.h"

int g_score = 0;
int g_sleepTime = 300;

void GoToPosition(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;

    if (x == 0 && y == 0) {
        return;
    }

    // �ƶ����λ��
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Update()
{
    for (int i = 0; i < snake.size; i++) {
        //��ʾ��
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
        GoToPosition(snake.body[i].x, snake.body[i].y);
        if (i == 0) {
            printf("@");
        } else {
            printf("#");
        }

        //��ʾʳ��
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);
        GoToPosition(food.x, food.y);
        printf("X");

        //������β
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 00);
        GoToPosition(tile_x, tile_y);
        printf(" ");

        //ѭ��״��
        if (isRool) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
            GoToPosition(tile_x, tile_y);
            printf("@");
        }
    }
}

void GameOver(int mode)
{
    if (mode == 1) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
        GoToPosition(snake.body[0].x, snake.body[0].y);
        printf("@");
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    GoToPosition(0, HEIGHT + 1);
    printf("GameOver");
    system("pause");
    exit(1);
}

int main()
{
    // ȥ������̨����
    CONSOLE_CURSOR_INFO cci;
    cci.bVisible = FALSE;
    cci.dwSize = sizeof(cci);
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);

    //���������
    srand((unsigned int)time(NULL));

    // ����ǽ����ɫ
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);

    //��ʼ��ǽ
    InitWall();

    //��ʼ����
    InitSnake();

    //��ʼ��ʳ��
    InitFood();

    //����
    Update();

    //�������
    char key = 'd'; //Ĭ������
    char preKey = 'd'; //��¼��һ�η���

    while (snake.body[0].x > 0 && snake.body[0].x < WIDTH - 2
        && snake.body[0].y > 0 && snake.body[0].y < HEIGHT - 2) {
        //���û�м������뷵��0
        if (_kbhit()) {
            //���ռ�������ķ���
            key = _getch();
        }

        if (key == 'd' && preKey == 'a' || key == 'a' && preKey == 'd' ||
            key == 'w' && preKey == 's' || key == 's' && preKey == 'w') {
            key = preKey;
        } else {
            preKey = key;
        }

        switch (key) {
            case 'w':
                offset_x = 0;
                offset_y = -1;
                break;
            case 's':
                offset_x = 0;
                offset_y = 1;
                break;
            case 'a':
                offset_x = -1;
                offset_y = 0;
                break;
            case 'd':
                offset_x = 1;
                offset_y = 0;
                break;
        }

        ////�����ƶ���
        //offset_x = 1;
        //offset_y = 0;

        //������Ƿ���ײ����
        for (int i = 1; i < snake.size; i++) {
            if (snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y) {
                GameOver(1);
            }
        }

        //�߳�ʳ��
        if (snake.body[0].x == food.x && snake.body[0].y == food.y) {
            snake.size++;
            g_score += 100;
            g_sleepTime > 50 ? (g_sleepTime -= 50) : (g_sleepTime = 50);
            InitFood(); //ˢ��ʳ��
        }

        // ��ʾ����
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
        GoToPosition(0, HEIGHT);
        printf("��ķ�����%d\n", g_score);

        //��¼��β��λ��
        tile_x = snake.body[snake.size - 1].x;
        tile_y = snake.body[snake.size - 1].y;

        //�ƶ�����
        for (int i = snake.size - 1; i > 0; i--) {
            snake.body[i].x = snake.body[i - 1].x;
            snake.body[i].y = snake.body[i - 1].y;
        }

        //�ƶ���ͷ
        snake.body[0].x += offset_x;
        snake.body[0].y += offset_y;

        //����Ƿ�ѭ��
        if (tile_x == snake.body[0].x && tile_y == snake.body[0].y) {
            isRool = 1;
        } else {
            isRool = 0;
        }

        //����
        Update();

        Sleep(g_sleepTime);
    }

    // system("pause");

    //ɾ����������
    //(void)getchar();

    GameOver(2);

    return EXIT_SUCCESS;
}