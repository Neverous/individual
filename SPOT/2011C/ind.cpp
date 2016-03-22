/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
#include<queue>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

unsigned int tests,
			 verts,
			 edges,
			 capacity,
			 start,
			 end,
			 result,
			 zombies[1048576];
int visited[1048576];
std::vector<unsigned int> graph[1048576];

std::queue<unsigned int> que;
unsigned int act;
static inline unsigned int BFS(void);

int main(void)
{
	scanf("%u", &tests);
	for(unsigned int t = 0; t < tests; ++ t)
	{
		scanf("%u %u %u", &verts, &edges, &capacity);
		for(unsigned int v = 0; v < verts; ++ v)
		{
			zombies[v] = 0;
			visited[v] = 0;
			graph[v].clear();
		}

		for(unsigned int e = 0; e < edges; ++ e)
		{
			scanf("%u %u", &start, &end);
			-- start;
			-- end;
			graph[start].push_back(end);
			graph[end].push_back(start);
		}

		result = BFS();
		if(result)
			printf("%u\n", result);

		else
			puts("hurray!");

	}

	return 0;
}

static inline unsigned int BFS(void)
{
	que = std::queue<unsigned int>();
	que.push(0);
	visited[0] = 1;
	while(!que.empty())
	{
		act = que.front();
		que.pop();
		for(unsigned int n = 0; n < graph[act].size(); ++ n)
		{
			if(visited[graph[act][n]])
				continue;

			if(++ zombies[visited[graph[act][n]] = visited[act] + 1] > capacity)
				return visited[act];

			que.push(graph[act][n]);
		}
	}

	return 0;
}
