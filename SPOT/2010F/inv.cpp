/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
#include<queue>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int tests,
	investments,
	benefits,
	investment,
	benefit,
	connections,
	result,
	//visited[256],
	level[256],
	cost[256][256];
std::vector<int> graph[256];

inline static int MIN(int a, int b);
//inline static int fordFulkerson(void);
//inline static int fordFulkersonDFS(int where, int end, int push, int flag);
inline static int dinitz(void);
inline static bool dinitzBFS(int from, int to);
inline static int dinitzDFS(int where, int end, int push);

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d %d", &investments, &benefits);
		for(int i = 1; i <= investments; ++ i)
		{
			scanf("%d", &investment);
			graph[investments + benefits + 1].push_back(i);
			graph[i].push_back(investments + benefits + 1);
			cost[i][investments + benefits + 1] = investment;
		}

		for(int b = 1; b <= benefits; ++ b)
		{
			scanf("%d", &benefit);
			graph[0].push_back(investments + b);
			graph[investments + b].push_back(0);
			cost[0][investments + b] = benefit;
			result += benefit;
		}

		scanf("%d", &connections);
		for(int c = 0; c < connections; ++ c)
		{
			scanf("%d %d", &investment, &benefit);
			graph[investment].push_back(investments + benefit);
			graph[investments + benefit].push_back(investment);
			cost[investments + benefit][investment] = (1 << 21);
			cost[investment][investments + benefit] = 0;
		}

		//result -= fordFulkerson();
		result -= dinitz();
		printf("%d\n", result);

		for(int v = 0; v < 256; ++ v)
		{
			graph[v].clear();
			//visited[v] = 0;
		}

		result = 0;
	}
	return 0;
}

/*
inline static int fordFulkerson(void)
{
	int flow = 0,
		act = 0,
		flag = 0;

	do
		flow += act = fordFulkersonDFS(0, investments + benefits + 1, (1 << 21), ++ flag);

	while(act);

	return flow;
}

inline static int fordFulkersonDFS(int where, int end, int push, int flag)
{
	if(where == end)
		return push;

	if(visited[where] == flag)
		return 0;

	visited[where] = flag;
	int tmp = 0;
	for(unsigned int n = 0; n < graph[where].size(); ++ n)
	{
		if(visited[graph[where][n]] == flag || !cost[where][graph[where][n]])
			continue;

		tmp = fordFulkersonDFS(graph[where][n], end, MIN(push, cost[where][graph[where][n]]), flag);
		if(tmp)
		{
			cost[where][graph[where][n]] -= tmp;
			cost[graph[where][n]][where] += tmp;
			return tmp;
		}
	}

	return 0;
}
*/
inline static int MIN(int a, int b)
{
	return a<b?a:b;
}

inline static int dinitz(void)
{
	int flow = 0,
		act = 0;

	while(dinitzBFS(0, investments + benefits + 1))
	{
		do
			flow += act = dinitzDFS(0, investments + benefits + 1, (1 << 21));

		while(act);
	}

	return flow;
}

inline static bool dinitzBFS(int from, int to)
{
	std::queue<int> que;
	int act;
	for(int v = 0; v < investments + benefits + 1; ++ v)
		level[v] = -1;

	level[to] = 0;
	que.push(to);
	while(!que.empty())
	{
		act = que.front();
		que.pop();
		for(unsigned int n = 0; n < graph[act].size(); ++ n)
		{
			if(cost[graph[act][n]][act] > 0 && level[graph[act][n]] == -1)
			{
				level[graph[act][n]] = level[act] + 1;
				que.push(graph[act][n]);
			}
		}
	}

	return level[from] >= 0;
}

inline static int dinitzDFS(int where, int end, int push)
{
	if(where == end)
		return push;

	int flow = 0;
	for(unsigned int n = 0; n < graph[where].size(); ++ n)
		if(cost[where][graph[where][n]] > 0 && level[graph[where][n]] == level[where] - 1)
		{
			flow = dinitzDFS(graph[where][n], end, MIN(push, cost[where][graph[where][n]]));
			if(flow)
			{
				cost[where][graph[where][n]] -= flow;
				cost[graph[where][n]][where] += flow;
				return flow;
			}
		}

	return 0;
}
