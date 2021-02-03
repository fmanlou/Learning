#include <stdio.h>

#define N 10
#define M 10

static int row = 0;
static int column = 0;
int array[N][M]; 

int maze(int r, int c)
{
    int res = -1;
    int cur;
    /* unable to forward */
    if(r > row - 1 || c > column - 1 || array[r][c] == 1)
        return -1;
    /* arrive the end point */
    if(r == row - 1 && c == column - 1)
        res = 0;

    cur = array[r][c];
    /* try to forward */
    array[r][c] = -1;
    if(res != 0 && array[r + 1][c] != -1)
        res = maze(r + 1, c);
    if(res != 0 && array[r][c + 1] != -1)
        res = maze(r, c + 1);
    if(res != 0 && array[r - 1][c] != -1)
        res = maze(r - 1, c);
    if(res != 0 && array[r][c - 1] != -1)
        res = maze(r, c - 1);
    /* failed, reset */
    if(res != 0)
        array[r][c] = cur;
    return res;
}

void print(int array[N][M])
{
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < column; j++)
        {
            if(array[i][j] == -1)
                printf("(%d,%d)\n", i, j);
        }
    }
}

int main()
{
    while(scanf("%d %d\n", &row, &column) == 2)
    {
        /* get array */
        for(int i = 0; i < row; i++)
        {
            int j = 0;
            while(1)
            {
                char c = getchar();
                if(c == '\n')
                    break;
                if(c == ' ')
                    continue;
                array[i][j++] = (int)(c - '0');
            }
        }
        maze(0, 0);
        print(array); 
    }
}
