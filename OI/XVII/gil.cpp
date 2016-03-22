/* 2009
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
#include<queue>

inline static void solve(void);
inline bool bfs(int vert, bool color = false);

int verts,
	edges,
	start,
	end;
char visited[200002];
std::vector<int> graph[200002];
std::queue<std::pair<int, bool> > que;
std::pair<int, bool> act;

int main(void)
{
	scanf("%d %d", &verts, &edges);
	for(int e = 0; e < edges; ++ e)
	{
		scanf("%d %d", &start, &end);
		-- start;
		-- end;
		graph[start].push_back(end);
		graph[end].push_back(start);
	}

	solve();
}

inline static void solve(void)
{
	bool possible = true;
	for(int v = 0; v < verts && possible; ++ v)
		if(!visited[v] && !bfs(v))
			possible = false;

	printf("%s\n", possible?"TAK":"NIE");
	if(!possible)
		return;

	for(int v = 0; v < verts; ++ v)
		printf("%s\n", visited[v] == 1?"K":"S");
}

inline bool bfs(int vert, bool color)
{
	que = std::queue<std::pair<int, bool> >();
	que.push(std::pair<int, bool>(vert, color));
	while(!que.empty())
	{
		act = que.front();
		que.pop();
		if(visited[act.first])
			continue;

		visited[act.first] = act.second + 1;
		for(unsigned int s = 0; s < graph[act.first].size(); ++ s)
			if(!visited[graph[act.first][s]])
				que.push(std::pair<int, bool>(graph[act.first][s], !act.second));
	}
	
	return graph[vert].size() > 0;
}

