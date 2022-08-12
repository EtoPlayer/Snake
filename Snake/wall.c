#include "wall.h"

// 初始化墙
void InitWall()
{
    for (int j = 0; j < HEIGHT; j++) {
        for (int i = 0; i < WIDTH; i++) {
            if (i == 0 || i == WIDTH - 1 || j == 0 || j == HEIGHT - 1) {
                printf("*");
            } else {
                printf(" ");
            }
        }

        if (j == 5) {
            printf("\t贪吃蛇");
        }
        if (j == 6) {
            printf("\tcreate by dyl");
        }
        if (j == 7) {
            printf("\tW: 向上");
        }
        if (j == 8) {
            printf("\tS: 向下");
        }
        if (j == 9) {
            printf("\tA: 向左");
        }
        if (j == 10) {
            printf("\tD: 向右");
        }
        printf("\n");
    }
}