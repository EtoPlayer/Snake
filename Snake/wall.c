#include "wall.h"

// ��ʼ��ǽ
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
            printf("\t̰����");
        }
        if (j == 6) {
            printf("\tcreate by dyl");
        }
        if (j == 7) {
            printf("\tW: ����");
        }
        if (j == 8) {
            printf("\tS: ����");
        }
        if (j == 9) {
            printf("\tA: ����");
        }
        if (j == 10) {
            printf("\tD: ����");
        }
        printf("\n");
    }
}