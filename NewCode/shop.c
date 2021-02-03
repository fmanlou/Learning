#include <stdio.h>

#define MAX 60

static int N;
static int m;
static int v[MAX];
static int p[MAX];
static int q[MAX];
static int c[MAX];

void print()
{
    printf("%d %d\n", N, m);
    for(int i = 0; i < m; i++)
    {
        printf("%d %d %d\n", v[i], p[i], q[i]);
    }
}

void swap(int i, int j)
{
    int temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;

    temp = p[i];
    p[i] = p[j];
    p[j] = temp;

    temp = q[i];
    q[i] = q[j];
    q[j] = temp;
}

int sort()
{
    for(int i = 0; i < m - 1; i++)
    {
        for(int j = i; j < m; j++)
        {
            if(v[i] > v[j])
                swap(i, j);
        }
    }
}

int buy()
{

}

int max(int money)
{
    if(buy() == 0)      

}

int main()
{
    scanf("%d %d", &N, &m);
    for(int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &v[i], &p[i], &q[i]);
    }
    //print();
}
