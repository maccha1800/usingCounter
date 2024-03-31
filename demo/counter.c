#include <stdio.h>
#include <string.h>
#include <time.h>

/*struct man
{
    int time;  // 残時間
} typedef Man;
*/

// カウンターを示す配列
int counter[5] = {0, 0, 0, 0, 0};

/*カウンターの状況を画面に出力する関数*/
void stateCounter(char *str)
{
    char time[10];

    // 人席目は仕切りを入れない
    sprintf(str, "%d", counter[0]);
    for (int i = 1; i < 5; i++)
    {
        sprintf(time, "%d", counter[i]);
        strcat(str, "|");
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
    int a = rand() % 8 + 1;

    for (int i = 0; i < 5; i++)
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
// TODO
// int calcUncomfortable()
// {
//     int score;
//     for (int i = 0; i < 4; i++)
//     {
//         if (counter[i] != 0 && counter[i] != 0)
//         {
//             score++;
//         }
//     }
// }

int main(void)
{
    srand((unsigned int)time(NULL));
    int count = 0;

    for (count = 0; count < 100; count++)
    {
        if (count % 4 == 0)
        {
            addMan();
        }

        char str[100];
        stateCounter(str);
        printf("%000d : %s\r\n", count, str);

        for (int i = 0; i < 5; i++)
        {
            if (counter[i] != 0)
            {
                counter[i]--;
            }
        }
    }

    return 0;
}