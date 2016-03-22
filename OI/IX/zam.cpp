/* 2009
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
#define DEBUG(args...) fprintf(stderr, args)
//#define DEBUG(args...) 

using namespace std;

int verts,
	edges,
	starting,
	ending,
	money,
	from,
	to,
	ticket[128];
bool visited[128][1024];

vector<int> result,
			graph[128];

void solve(void);
bool dfs(int vert, int end, int cash);

int main(void)
{
	scanf("%d %d %d %d %d", &verts, &edges, &starting, &ending, &money);
	-- starting;
	-- ending;
	for(int v = 0; v < verts; ++ v)
		scanf("%d", &ticket[v]);

	for(int e = 0; e < edges; ++ e)
	{
		scanf("%d %d", &from, &to);
		-- from;
		-- to;
		graph[from].push_back(to);
		graph[to].push_back(from);
	}

	solve();
	return 0;
}

void solve(void)
{
	dfs(starting, ending, money);
	for(int r = (int)result.size() - 1; r >= 0; -- r)
		printf("%d ", result[r] + 1);

	puts("");
	return;
}

bool dfs(int vert, int end, int cash)
{
	cash -= ticket[vert];
	visited[vert][cash] = true;
	if(cash == 0)
	{
		if(vert != end)
			return false;
		
		result.push_back(vert);
		return true;
	}

	for(unsigned int s = 0; s < graph[vert].size(); ++ s)
	{
		if(ticket[graph[vert][s]] > cash || visited[graph[vert][s]][cash - ticket[graph[vert][s]]])
			continue;

		if(dfs(graph[vert][s], end, cash))
		{
			result.push_back(vert);
			return true;
		}
	}

	return false;
}
