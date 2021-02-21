#include <stdio.h>

#define inf 100000
#define V_SIZE 6

void array_fill(int *array, int len, int val)
{
	for(int i = 0; i < len; i++)
	{
		array[i] = val;
	}
}

void dijkstra(int graph[][V_SIZE], int n, int start, int dist[])
{
	int *shortest_path = (int *)malloc(sizeof(int) * n);
	int *mark=(int *)malloc(sizeof(int) * n);
	int *path = (int *)malloc(sizeof(int) * n);

	array_fill(mark, n, 0);
	array_fill(dist, n, inf);

	for(int i = 0; i < n; i++)
	{
		dist[i] = graph[start][i];
		if(i != start && dist[i] < inf) 
			path[i] = start;
		else 
			path[i] = -1;
	}

	mark[start] = 1;
	
	while(1)
	{
		min = inf;
		v = -1;
		for(int i = 0; i < n; i++)
		{
			if(!mark[i])
			{
				if(dist[i] < min)
				{
					min = dist[i];
					v = i;
				}
			}
		}

		if(v == -1)
		greak;:
	}
}

int main()
{
	int dist[V_SIZE];
	int W[V_SIZE][V_SIZE] = {
		{ 0, 1, 4, inf, inf ,inf },
		{ 1, 0, 2, 7, 5, inf },
		{ 4, 2, 0, inf, 1, inf },
		{ inf, 7, inf, 0, 3, 2 },
		{ inf, 5, 1, 3, 0, 6 },
		{ inf, inf, inf, 2, 6, 0 }
	};
}
