/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<list>

int verts,
	edges,
	from,
	to,
	before,
	after,
	weight[131072],
	result;
bool possible = true,
	 doing = false,
	 visited[131072],
	 used[1048576];
std::list<std::pair<int, int> > graph[131072];
std::list<int> cycle[131072];

inline static int DFS(const int &a);

int main(void)
{
	scanf("%d %d", &verts, &edges);
	for(int e = 0; e < edges; ++ e)
	{
		scanf("%d %d %d %d", &from, &to, &before, &after);
		if(before == after)
			continue;

		doing = true;
		-- from;
		-- to;
		graph[from].push_back(std::make_pair(to, e));
		graph[to].push_back(std::make_pair(from, e));
		++ weight[to];
		++ weight[from];
	}

	if(!doing)
	{
		puts("0");
		return 0;
	}

	for(int v = 0; possible && v < verts; ++ v)
		possible = weight[v] % 2 == 0;

	if(!possible)
	{
		puts("NIE");
		return 0;
	}

	for(int v = 0; v < verts; ++ v)
		DFS(v);

	printf("%d\n", result);
	for(int r = 0; r < result; ++ r)
	{
		printf("%d ", cycle[r].size() - 1);
		for(std::list<int>::iterator c = cycle[r].begin(); c != cycle[r].end(); ++ c)
			printf("%d ", *c + 1);

		puts("");
	}

	return 0;
}

inline static int DFS(const int &a)
{
	int c = -1;
	visited[a] = true;
	for(std::list<std::pair<int, int> >::iterator v = graph[a].begin(); v != graph[a].end(); ++ v)
	{
		if(used[v->second])
		{
			v = -- graph[a].erase(v);
			continue;
		}

		used[v->second] = true;
		if(visited[v->first])
		{
			visited[a] = false;
			cycle[result].push_front(v->first);
			return v->first;
		}

		c = DFS(v->first);
		if(c != a)
		{
			visited[a] = false;
			cycle[result].push_front(v->first);
			return c;
		}

		cycle[result].push_front(v->first);
		cycle[result].push_front(a);
		++ result;
	}

	visited[a] = false;
	return c;
}

