/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 * ----------
 *  BRUTE
 */
#include<cstdio>
#include<vector>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int verts,
	edges,
	start,
	end,
	count,
	order[262144],
	component[262144],
	ccount[262144],
	ctcount[262144],
	compCount = 1,
	result;
bool articulationPoint[262144];
bool destroyed[262144];
std::vector<int> graph[262144],
				 unassigned, // verts not assigned to component
				 unknown; // verts not known if in different components

inline static void DFS(const int &v);

int main(void)
{
	scanf("%d %d", &verts, &edges);
	for(int e = 0; e < edges; ++ e)
	{
		scanf("%d %d", &start, &end);
		-- start;
		-- end;
		graph[start].push_back(end);
	}

	for(int v = 0; v < verts; ++ v)
		if(!order[v])
			DFS(v);

	for(int c = 0; c <= compCount; ++ c)
		ctcount[c] = ccount[c];

	result = compCount - 1;
	for(int v = 0; v < verts; ++ v)
	{
		if(ctcount[component[v]] == 1)
			continue;

		destroyed[v] = true;
		for(int w = 0; w < verts; ++ w)
		{
			order[w] = 0;
			component[w] = 0;
		}

		compCount = 1;
		count = 0;
		for(int w = 0; w < verts; ++ w)
			if(!destroyed[w] && !order[w])
				DFS(w);

		if(compCount - 1 != result)
			articulationPoint[v] = true;

		destroyed[v] = false;
	}

	printf("%d\n", result);
	for(int v = 0; v < verts; ++ v)
		puts(articulationPoint[v]?"TAK":"NIE");

	return 0;
}

inline static void DFS(const int &v)
{
	order[v] = ++ count;
	unassigned.push_back(v);
	unknown.push_back(v);
	for(unsigned int n = 0; n < graph[v].size(); ++ n)
	{
		if(destroyed[graph[v][n]])
			continue;

		if(!order[graph[v][n]])
			DFS(graph[v][n]);

		else if(!component[graph[v][n]])
			while(order[unknown.back()] > order[graph[v][n]])
				unknown.pop_back();
	}

	if(v == unknown.back())
	{
		ccount[compCount] = 1;
		while(unassigned.back() != v)
		{
			component[unassigned.back()] = compCount;
			++ ccount[compCount];
			unassigned.pop_back();
		}

		component[v] = compCount ++;
		unassigned.pop_back();
		unknown.pop_back();
	}
}
