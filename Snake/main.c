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

    // 移动光标位置
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Update()
{
    for (int i = 0; i < snake.size; i++) {
        //显示蛇
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
        GoToPosition(snake.body[i].x, snake.body[i].y);
        if (i == 0) {
            printf("@");
        } else {
            printf("#");
        }

        //显示食物
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);
        GoToPosition(food.x, food.y);
        printf("X");

        //更新蛇尾
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 00);
        GoToPosition(tile_x, tile_y);
        printf(" ");

        //循环状况
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
    // 去除控制台坐标
    CONSOLE_CURSOR_INFO cci;
    cci.bVisible = FALSE;
    cci.dwSize = sizeof(cci);
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);

    //随机数种子
    srand((unsigned int)time(NULL));

    // 设置墙的颜色
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);

    //初始化墙
    InitWall();

    //初始化蛇
    InitSnake();

    //初始化食物
    InitFood();

    //更新
    Update();

    //方向变量
    char key = 'd'; //默认向右
    char preKey = 'd'; //记录上一次方向

    while (snake.body[0].x > 0 && snake.body[0].x < WIDTH - 2
        && snake.body[0].y > 0 && snake.body[0].y < HEIGHT - 2) {
        //如果没有键盘输入返回0
        if (_kbhit()) {
            //接收键盘输入的方向
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

        ////设置移动量
        //offset_x = 1;
        //offset_y = 0;

        //检测蛇是否碰撞自身
        for (int i = 1; i < snake.size; i++) {
            if (snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y) {
                GameOver(1);
            }
        }

        //蛇吃食物
        if (snake.body[0].x == food.x && snake.body[0].y == food.y) {
            snake.size++;
            g_score += 100;
            g_sleepTime > 50 ? (g_sleepTime -= 50) : (g_sleepTime = 50);
            InitFood(); //刷新食物
        }

        // 显示分数
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
        GoToPosition(0, HEIGHT);
        printf("你的分数：%d\n", g_score);

        //记录蛇尾的位置
        tile_x = snake.body[snake.size - 1].x;
        tile_y = snake.body[snake.size - 1].y;

        //移动蛇身
        for (int i = snake.size - 1; i > 0; i--) {
            snake.body[i].x = snake.body[i - 1].x;
            snake.body[i].y = snake.body[i - 1].y;
        }

        //移动蛇头
        snake.body[0].x += offset_x;
        snake.body[0].y += offset_y;

        //检测是否循环
        if (tile_x == snake.body[0].x && tile_y == snake.body[0].y) {
            isRool = 1;
        } else {
            isRool = 0;
        }

        //更新
        Update();

        Sleep(g_sleepTime);
    }

    // system("pause");

    //删除无用描述
    //(void)getchar();

    GameOver(2);

    return EXIT_SUCCESS;
}