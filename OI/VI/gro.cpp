/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
#include<queue>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int chambers,
	tunnels,
	chamber,
	weight[256][256],
	level[256],
	latest[256],
	qact;
bool impossible[256];
std::vector<int> graph[256];
std::queue<int> que;

inline static int MIN(const int &a, const int &b){return a<b?a:b;}
inline static bool dinicBFS(const int &start, const int &end);
inline static int dinicDFS(const int &v, const int &end, int push = 1 << 20);
inline static int dinic(const int &start, const int &end);

int main(void)
{
	scanf("%d", &chambers);
	for(int c = 0; c < chambers - 1; ++ c)
	{
		scanf("%d", &tunnels);
		for(int t = 0; t < tunnels; ++ t)
		{
			scanf("%d", &chamber);
			-- chamber;
			graph[c].push_back(chamber);
			graph[chamber].push_back(c);
			weight[c][chamber] = 1 << 20;
			weight[chamber][c] = 0;
		}
	}

	for(unsigned int n = 0; n < graph[0].size(); ++ n)
	{
		weight[0][graph[0][n]] = 1;
		weight[graph[0][n]][0] = 0;
	}

	for(unsigned int n = 0; n < graph[chambers - 1].size(); ++ n)
	{
		weight[graph[chambers - 1][n]][chambers - 1] = 1;
		weight[chambers - 1][graph[chambers - 1][n]] = 0;
	}

	printf("%d\n", dinic(0, chambers - 1));
	return 0;
}

inline static int dinic(const int &start, const int &end)
{
	int flow = 0,
		act = 0;

	while(dinicBFS(end, start))
		do
			flow += act = dinicDFS(start, end);

		while(act);

	return flow;
}

inline static bool dinicBFS(const int &start, const int &end)
{
	que = std::queue<int>();
	for(int c = 0; c < chambers; ++ c)
	{
		level[c] = -1;
		latest[c] = 0;
	}

	level[start] = 0;
	que.push(start);
	while(!que.empty() && level[end] == -1)
	{
		qact = que.front();
		que.pop();

		for(unsigned int n = 0; n < graph[qact].size(); ++ n)
			if(level[graph[qact][n]] == -1 && weight[graph[qact][n]][qact] != 0)
			{
				level[graph[qact][n]] = level[qact] + 1;
				que.push(graph[qact][n]);
			}

	}

	return level[end] != -1;
}

inline static int dinicDFS(const int &v, const int &end, int push)
{
	if(!push || v == end)
		return push;

	int flow = 0,
		act;

	for(unsigned int n = latest[v]; push && n < graph[v].size(); n = ++ latest[v])
		if(!impossible[v] && level[graph[v][n]] + 1 == level[v] && weight[v][graph[v][n]])
		{
			act = dinicDFS(graph[v][n], end, MIN(weight[v][graph[v][n]], push));
			if(act)
			{
				flow += act;
				push -= act;
				weight[v][graph[v][n]] -= act;
				weight[graph[v][n]][v] += act;
			}
		}

	latest[v] -= !push;
	impossible[v] = !flow;
	return flow;
}
