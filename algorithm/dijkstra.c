#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAXSIZE 60

void dijkstra(int graph[][6], int size, int start)
{
	int visit[MAXSIZE] = {0};
	int parent[MAXSIZE] = {0};
	int frontier[MAXSIZE] = {0};
	int next[MAXSIZE] = {0};
	int dist[MAXSIZE] = {0};
	bool is_empty = false;

	for(int i = 0; i < size; i++)
	{
		dist[i] = 1000;
	}

	frontier[start] = 1;
	parent[start] = start;
	dist[start] = 0;
	while(!is_empty)
	{
		is_empty = true;
		memset(next, 0, sizeof(next));
		for(int i = 0; i < size; i++)
		{
			if(frontier[i] == 0)
				continue;

			for(int j = 0;  j < size; j++)
			{
				if(graph[i][j] == -1 && graph[i][j] != 0)
					continue;

				if(visit[j] != 1)
				{
					is_empty = false;
					next[j] = 1;
				}

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

	for(int i = 0; i < size; i++)
		printf("%d %d %d\n", i, dist[i], parent[i]);
}

void test_suite1()
{
	int W[][6] = {
		{ 0, 1, 4, -1, -1 ,-1 },
		{ 1, 0, 2, 7, 5, -1 },
		{ 4, 2, 0, -1, 1, -1 },
		{ -1, 7, -1, 0, 3, 2 },
		{ -1, 5, 1, 3, 0, 6 },
		{ -1, -1, -1, 2, 6, 0 }
	};
	dijkstra(W, 6, 0);
}

void test_suite2()
{
	int W[][6] = {
		{ 0, 1, 4, -1, -1 ,-1 },
		{ 1, 0, 2, 7, 5, -1 },
		{ 4, 2, 0, -1, 1, -1 },
		{ -1, 7, -1, 0, 3, 2 },
		{ -1, 5, 1, 3, 0, 6 },
		{ -1, -1, -1, 2, 6, 0 }
	};
	dijkstra(W, 6, 0);
}

int main()
{
	test_suite1();
	test_suite2();
}
