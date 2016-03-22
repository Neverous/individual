/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
#include<queue>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int verts,
	edges,
	from,
	to,
	act;
bool visited[40004];
std::vector<int> graph[40004],
				 layer[7];
std::queue<int> que;

inline static int MAX(const int &a, const int &b){return a>b?a:b;}
inline static void BFS(const int &start);

int main(void)
{
	scanf("%d %d", &verts, &edges);
	for(int e = 0; e < edges; ++ e)
	{
		scanf("%d %d", &from, &to);
		-- from;
		-- to;
		graph[from].push_back(to);
		graph[to].push_back(from);
	}

	BFS(0); BFS(1);
	for(int v = 0; v < verts; ++ v)
		if(!visited[v])
			layer[3].push_back(v);

	printf("%d\n", (int)
		(layer[0].size() * (layer[0].size() + layer[1].size() - 1) +
		layer[1].size() * (layer[0].size() + layer[1].size() + layer[2].size() - 1) +
		layer[2].size() * (layer[1].size() + layer[2].size() + layer[3].size() + layer[4].size() - 1) +
		layer[3].size() * (layer[2].size() + layer[3].size() + layer[4].size() + 2 * MAX(layer[1].size(), layer[5].size()) - 1) +
		layer[4].size() * (layer[2].size() + layer[3].size() + layer[4].size() + layer[5].size() - 1) +
		layer[5].size() * (layer[4].size() + layer[5].size() + layer[6].size() - 1) +
		layer[6].size() * (layer[6].size() + layer[5].size() - 1)) / 2 -
		edges);

	return 0;
}

inline static void BFS(const int &start)
{
	std::vector<int> *F,
					 *S,
					 *T;
	if(start) {F = &layer[6]; S = &layer[5]; T = &layer[4];}
	else {F = &layer[0]; S = &layer[1]; T = &layer[2];}

	visited[start] = true;
	F->push_back(start);
	for(unsigned int n = 0, v; n < graph[start].size(); ++ n)
	{
		v = graph[start][n];
		if(visited[v])
			continue;

		visited[v] = true;
		que.push(v);
		S->push_back(v);
	}

	while(!que.empty())
	{
		act = que.front();
		que.pop();
		for(unsigned int n = 0, v; n < graph[act].size(); ++ n)
		{
			v = graph[act][n];
			if(visited[v])
				continue;

			visited[v] = true;
			T->push_back(v);
		}
	}

	return;
}
