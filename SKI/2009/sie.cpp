/* 2009
 * Maciej Szeptuch
 * XIV LO Wrocław
 * */
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

int tests,
	verts,
	edges,
	from,
	to,
	wireless,
	visited[10002],
	low[10002],
	fathers[10002],
	result;

vector<int> graph[10002];

void dfs(int vertex, int father, int time);

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		result = 0;
		for(int v = 0; v <= verts; ++ v)
		{
			graph[v].clear();
			visited[v] = low[v] = fathers[v] = 0;
		}

		scanf("%d %d", &verts, &edges);
		for(int e = 0; e < edges; ++ e)
		{
			scanf("%d %d", &from, &to);
			-- from;
			-- to;
			graph[from].push_back(to);
			graph[to].push_back(from);
		}

		scanf("%d", &wireless);
		for(int w = 0; w < wireless; ++ w)
		{
			scanf("%d", &to);
			-- to;
			graph[verts].push_back(to);
			graph[to].push_back(verts);
		}

		for(int v = 0; v < verts; ++ v)
			if(!visited[v])
				dfs(v, -1, 1);

		printf("%s\n", result?"NIE":"TAK");
	}
}

void dfs(int vertex, int father, int time)
{
	int flag = 0;
	fathers[vertex] = father;
	low[vertex] = visited[vertex] = time;
	for(unsigned int s = 0; s < graph[vertex].size(); ++ s)
	{
		if(!visited[graph[vertex][s]])
		{
			dfs(graph[vertex][s], vertex, time + 1);
			if(low[graph[vertex][s]] >= visited[vertex] && (graph[vertex][s] != verts || wireless != 1))
				++ flag;
		}

		if(graph[vertex][s] != father)
			low[vertex]=(low[vertex] < low[graph[vertex][s]])?low[vertex]:low[graph[vertex][s]];
	}

	if((father != -1 && flag > 0) || (father == -1 && flag > 1))
		if(vertex != verts)
			++ result;

	return;
}
