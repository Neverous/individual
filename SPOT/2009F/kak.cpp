/* 2009
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<cstdlib>
#include<vector>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...) 

using namespace std;

int tests,
	verts,
	edges,
	start,
	end,
	visited[1000001],
	answer,
	time,
	tResult;
vector<int> graph[1000001];

int solve(int begin);
int dfsCount(int vert, int father);

int main(void)
{
	scanf("%d", &tests);
	srand(1337 + tests);
	for(int t = 0; t < tests; ++ t)
	{
		DEBUG("TEST %d\n__________\n", t + 1);
		scanf("%d %d", &verts, &edges);
		for(int v = 0; v < verts; ++ v)
		{
			visited[v] = 0;
			graph[v].clear();
		}

		for(int e = 0; e < edges; ++ e)
		{
			scanf("%d %d", &start, &end);
			graph[start].push_back(end);
			graph[end].push_back(start);
		}

		answer = solve(rand() % verts);
		if(answer == -1)
			printf("NIE\n");

		else
			printf("%d\n", answer);

		DEBUG("----------\n");
	}

	return 0;
}

int solve(int begin)
{
	tResult = 0;
	time = 1;
	int temp = dfsCount(begin, -1);
	if(temp == -1)
		return -1;
	
	for(int v = 0; v < verts; ++ v)
		if(!visited[v])
		{
			temp= dfsCount(v, -1);
			if(temp == -1)
				return -1;
		}

	DEBUG("WYNIK: %d\n", tResult);
	return tResult;
}

int dfsCount(int vert, int father)
{
	int act = 0,
		tmp;
	visited[vert] = time ++;
	DEBUG("BADAM %d\n", vert);
	for(unsigned int s = 0; s < graph[vert].size(); ++ s)
	{
		if(graph[vert][s] == father)
			continue;

		DEBUG("\tSYN %d\n", graph[vert][s]);
		if(!visited[graph[vert][s]])
		{
			tmp = dfsCount(graph[vert][s], vert);
			if(tmp == -1)
				return -1;

			act += tmp;
			DEBUG("PO ODWIEDZINACH %d: %d\n", graph[vert][s], act);
			continue;
		}

		if(visited[graph[vert][s]] < visited[vert])
		{
			++ act;
			tResult += 1;
		}
		// mam wsteczną krawędź do góry

		if(visited[graph[vert][s]] > visited[vert])
			-- act;
		// koniec jakiejś wstecznej krawędzi
		
		if(act > 1)
			return -1;

		DEBUG("AKTUALNY: %d\n", act);
	}
	DEBUG("------\n");
	return act;
}
