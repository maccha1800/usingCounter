#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*struct man
{
    int time;  // 残時間
} typedef Man;
*/

int *counter; // カウンター
int SeetNum;  // 席数
int *LWall;   // 壁(左)
int *RWall;   // 壁(右)

/* カウンターの初期設定(入力は席数)  */
void initializeCounter(int n)
{
    SeetNum = n;
    LWall = (int *)malloc(sizeof(int) * (SeetNum + 2));
    counter = LWall + 1;
    RWall = LWall + SeetNum + 1;

    *LWall = 0;
    *RWall = 0;

    for (int i = 0; i < SeetNum; i++)
    {
        counter[i] = 0;
    }

    printf("addres-------\r\nLWall   : %p\r\ncounter : %p\r\nRWall   : %p\r\n-------------\r\n\r\n", LWall, counter, RWall);
}

void finalizeCounter()
{
    free(LWall);
}

/*カウンターの状況を画面に出力する関数*/
void stateCounter(char *str)
{
    char time[10];

    // 1席目は仕切りを入れない
    sprintf(str, "%3d", counter[0]);
    for (int i = 1; i < SeetNum; i++)
    {
        sprintf(time, "%3d", counter[i]);
        strcat(str, " | ");
        strcat(str, time);
    }
}

/*
カウンターに人間を追加する
人間を追加できた場合は0を返し，投入できない場合1を返す．
*/
int addMan()
{
    // 滞在時間算出（最大値8）
    int a = rand() % 16 + 1;

    for (int i = 0; i < SeetNum; i++)
    {
        if (counter[i] == 0)
        {
            // 人がいない場合に，人を投入する．
            counter[i] = a;
            return 1;
        }
    }
    return 0;
}

// 不快度の総量を計算する関数
int calcUncomfortable()
{
    int score = 0;
    int left;
    int right;

    // 人の隣に人がいる場合、一人につき不快度を1数える
    for (int i = 0; i < SeetNum; i++)
    {
        int *seet = counter + i;

        if (*seet == 0)
        {
            continue;
        }

        left = *(seet - 1);
        right = *(seet + 1);

        if (left != 0)
            score++;
        if (right != 0)
            score++;
    }
    return score;
}

int main(void)
{
    srand((unsigned int)time(NULL));

    printf("start\r\n");

    char str[100];

    initializeCounter(5);
    stateCounter(str);
    printf("s : %s\r\n", str);

    int count = 0;

    for (count = 0; count < 100; count++)
    {
        if (count % 4 == 0)
        {
            addMan();
        }

        stateCounter(str);
        printf("%03d : %s  (%d)\r\n", count, str, calcUncomfortable());

        for (int i = 0; i < SeetNum; i++)
        {
            if (counter[i] != 0)
            {
                counter[i]--;
            }
        }
    }

    finalizeCounter();

    printf("finish\r\n");
    return 0;
}