/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int metals,
	custom[5005],
	transformations,
	from,
	to,
	cost,
	forward[5005],
	backward[5005],
	cheapest = 1 << 29;
std::vector<std::pair<int, int> > normal[5005],
								  reversed[5005];
std::priority_queue<std::pair<int, int> > que;
std::pair<int, int> act;

inline static void dijkstra(const int &start, const std::vector<std::pair<int, int> > *graph, int *result);

int main(void)
{
	scanf("%d", &metals);
	for(int m = 0; m < metals; ++ m)
	{
		scanf("%d", &custom[m]);
		custom[m] /= 2;
		forward[m] = backward[m] = 1 << 29;
	}

	scanf("%d", &transformations);
	for(int t = 0; t < transformations; ++ t)
	{
		scanf("%d %d %d", &from, &to, &cost);
		-- from;
		-- to;
		normal[from].push_back(std::make_pair(to, cost));
		reversed[to].push_back(std::make_pair(from, cost));
	}

	for(int m = 0; m < metals; ++ m)
	{
		std::random_shuffle(normal[m].begin(), normal[m].end());
		std::random_shuffle(reversed[m].begin(), reversed[m].end());
	}

	dijkstra(0, normal, forward);
	dijkstra(0, reversed, backward);
	for(int m = 0; m < metals; ++ m)
		if(cheapest > forward[m] + backward[m] + custom[m])
			cheapest = forward[m] + backward[m] + custom[m];

	printf("%d\n", cheapest);
	return 0;
}

inline static void dijkstra(const int &start, const std::vector<std::pair<int, int> > *graph, int *result)
{
	que = std::priority_queue<std::pair<int, int> >();
	result[start] = 0;
	que.push(std::make_pair(0, start));

	while(!que.empty())
	{
		act = que.top();
		que.pop();
		if(-act.first > result[act.second])
			continue;

		for(unsigned int n = 0, v, c; n < graph[act.second].size(); ++ n)
		{
			v = graph[act.second][n].first;
			c = graph[act.second][n].second;
			if(result[v] <= result[act.second] + c)
				continue;

			result[v] = result[act.second] + c;
			que.push(std::make_pair(-result[v], v));
		}
	}

	return;
}
