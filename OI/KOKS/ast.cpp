/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<queue>
#include<vector>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int verts,
	shelters,
	edges,
	shelter,
	start,
	end,
	cost,
	max,
	length[1024];
std::pair<int, int> act;
std::priority_queue<std::pair<int, int> > que;
std::vector<std::pair<int, int> > graph[1024];

int main(void)
{
	scanf("%d %d %d", &verts, &shelters, &edges);
	for(int v = 0; v < verts; ++ v)
		length[v] = (1 << 30);

	for(int s = 0; s < shelters; ++ s)
	{
		scanf("%d", &shelter);
		length[-- shelter] = 0;
		que.push(std::make_pair(0, shelter));
	}

	for(int e = 0; e < edges; ++ e)
	{
		scanf("%d %d %d", &start, &end, &cost);
		-- start;
		-- end;
		graph[start].push_back(std::make_pair(end, cost));
		graph[end].push_back(std::make_pair(start, cost));
	}

	while(!que.empty())
	{
		act = que.top();
		que.pop();
		act.first *= -1;
		if(length[act.second] < act.first)
			continue;

		for(unsigned int n = 0; n < graph[act.second].size(); ++ n)
			if(act.first + graph[act.second][n].second < length[graph[act.second][n].first])
			{
				length[graph[act.second][n].first] = act.first + graph[act.second][n].second;
				que.push(std::make_pair(-length[graph[act.second][n].first], graph[act.second][n].first));
			}
	}

	for(int v = 0; v < verts; ++ v)
		max = (max < length[v])?length[v]:max;

	printf("%d\n", max);
	return 0;
}

