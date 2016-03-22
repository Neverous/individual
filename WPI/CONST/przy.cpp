/* 2009
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<algorithm>
#include<vector>

int verts,
	edges,
	resistance[500005],
	start,
	end,
	result[500005],
	r;
bool visited[500005];
std::vector<int> graph[500005];

int dfs(int vert);

int main(void)
{
	scanf("%d %d", &verts, &edges);
	for(int v = 0; v < verts; ++ v)
		scanf("%d", &resistance[v]);

	for(int e = 0; e < edges; ++ e)
	{
		scanf("%d %d", &start, &end);
		-- start;
		-- end;
		graph[start].push_back(end);
		graph[end].push_back(start);
	}

	for(int v = 0; v < verts; ++ v)
	{
		if(visited[v])
			continue;

		result[r ++] = dfs(v);
	}
	
	std::sort(result, result + r);
	printf("%d\n", r);
	for(int p = 0; p < r; ++ p)
		printf("%d\n", result[p]+1);

	return 0;
}

int dfs(int vert)
{
	int result = vert,
		tmp;

	visited[vert] = true;
	for(unsigned int i = 0; i < graph[vert].size(); ++ i)
	{
		if(visited[graph[vert][i]])
			continue;
		
		tmp = dfs(graph[vert][i]);
		if(resistance[tmp] < resistance[result] || (resistance[tmp] == resistance[result] && tmp < result))
			result  = tmp;
	}

	return result;
}
