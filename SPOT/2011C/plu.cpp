/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
#include<list>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

unsigned int tests,
			 verts,
			 edges,
			 from,
			 to,
			 plow,
			 weight[131072];
bool edge[1048576],
	 visited[131072];
std::vector<std::pair<unsigned int, unsigned int> > graph[131072];
std::list<unsigned int> route[131072];

static inline void trace(unsigned int v, unsigned int dest);

int main(void)
{
	scanf("%u", &tests);
	for(unsigned int t = 0; t < tests; ++ t)
	{
		scanf("%u %u", &verts, &edges);
		for(unsigned int e = 0; e < edges; ++ e)
		{
			scanf("%u %u", &from, &to);
			-- from;
			-- to;
			edge[e] = true;
			++ weight[from];
			++ weight[to];
			graph[from].push_back(std::make_pair(to, e));
			graph[to].push_back(std::make_pair(from, e));
		}

		plow = 0;
		for(unsigned int v = 0; v < verts; ++ v)
			visited[v] = false;

		for(unsigned int v = 0; v < verts; ++ v)
		{
			if(visited[v] || weight[v] % 2 == 0)
				continue;

			trace(v, plow ++);
			if(plow && route[plow - 1].size() == 1)
				route[-- plow].clear();
		}

		for(unsigned int v = 0; v < verts; ++ v)
		{
			if(visited[v])
				continue;

			trace(v, plow ++);
			if(plow && route[plow - 1].size() == 1)
				route[-- plow].clear();
		}

		printf("%u\n", plow);
		for(unsigned int p = 0; p < plow; ++ p)
		{
			printf("%u ", (unsigned int)route[p].size());
			for(std::list<unsigned int>::iterator r = route[p].begin(); r != route[p].end(); ++ r)
				printf("%u ", *r);

			puts("");
		}
	}

	return 0;
}

static inline void trace(unsigned int v, unsigned int dest)
{
	visited[v] = true;
	for(unsigned int n = 0; n < graph[v].size(); ++ n)
	{
		if(!edge[graph[v][n].second])
			continue;

		edge[graph[v][n].second] = false;
		trace(graph[v][n].first, dest);
	}

	route[dest].push_front(v + 1);
	return;
}

