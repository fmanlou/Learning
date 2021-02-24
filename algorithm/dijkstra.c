#include <stdio.h>
#include <string.h>

#define V_SIZE 6

int is_empty(int *array)
{
	for(int i = 0; i < V_SIZE; i++)
	{
		if(array[i] != 0)
			return 0;
	}

	return 1;
}

void dijkstra(int graph[][V_SIZE], int start)
{
	int visit[V_SIZE] = {0};
	int parent[V_SIZE] = {0};
	int frontier[V_SIZE] = {0};
	int next[V_SIZE] = {0};
	int dist[V_SIZE] = {0};

	for(int i = 0; i < V_SIZE; i++)
	{
		dist[i] = 1000;
	}

	frontier[start] = 1;
	parent[start] = start;
	dist[start] = 0;
	while(!is_empty(frontier))
	{
		for(int i = 0; i < V_SIZE; i++)
		{
			if(frontier[i] == 0)
				continue;

			memset(next, 0, sizeof(next));
			for(int j = 0;  j < V_SIZE; j++)
			{
				if(graph[i][j] == -1 && graph[i][j] != 0)
					continue;

				if(visit[j] != 1)
					next[j] = 1;

				if(dist[j] > graph[i][j] + dist[i])
				{
					dist[j] =  graph[i][j] + dist[i];
					parent[j] = i;
				}
			}
			visit[i] = 1;
		}
		memcpy(frontier, next, sizeof(frontier));
	}

	for(int i = 0; i < V_SIZE; i++)
		printf("%d %d %d\n", i, dist[i], parent[i]);
}

int main()
{
	int W[V_SIZE][V_SIZE] = {
		{ 0, 1, 4, -1, -1 ,-1 },
		{ 1, 0, 2, 7, 5, -1 },
		{ 4, 2, 0, -1, 1, -1 },
		{ -1, 7, -1, 0, 3, 2 },
		{ -1, 5, 1, 3, 0, 6 },
		{ -1, -1, -1, 2, 6, 0 }
	};
	dijkstra(W, 0);
}
