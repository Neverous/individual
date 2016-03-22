/* 2009
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
#include<cstdlib>

using namespace std;

int verts,
	edges,
	newedges,
	start,
	end,
	vert[200002],
	count;
vector<int> graph[200002];

void preprocess(int begin);
void dfsNumber(int v);

int main(void)
{
	scanf("%d %d %d", &verts, &edges, &newedges);
	srand(192705231 + verts);
	for(int e = 0; e < edges; ++ e)
	{
		scanf("%d %d", &start, &end);
		graph[start].push_back(end);
	}

	preprocess(rand() % verts);
	for(int n = 0; n < newedges; ++ n)
	{
		scanf("%d %d", &start, &end);
		printf("%d\n", vert[start] < vert[end]?1:0);
	}
	return 0;
}

void preprocess(int begin)
{
	dfsNumber(begin);
	for(int v = 0; v < verts; ++ v)
		if(!vert[v])
			dfsNumber(v);

	return;
}

void dfsNumber(int v)
{
	vert[v] = 1;
	for(unsigned int s = 0; s < graph[v].size(); ++ s)
		if(!vert[graph[v][s]])
			dfsNumber(graph[v][s]);

	vert[v] = ++ count;
}
