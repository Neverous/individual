/* 2010
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
#include<queue>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int size,
	cost;
long long int distance[1000010];

std::pair<long long int, int> act;
std::vector<std::pair<int, long long int> > graph[1000010];
std::priority_queue<std::pair<long long int, int>, std::vector<std::pair<long long int, int> >, std::greater<std::pair<long long int, int> > > que;

void dijkstra(void);

int main(void)
{
	scanf("%*d"); // Liczba zestawów testowych O.o ?Z = 1?
	scanf("%d", &size);
	for(int h = 0; h < 2 * size + 1; ++ h)
		for(int w = 0; w < size + h % 2; ++ w)
		{
			scanf("%d", &cost);
			DEBUG("%d: ", h);
			if(h % 2)
			{
				if(w == 0)
				{
					graph[0].push_back(std::pair<int, long long int>((h - 1) * size / 2 + 1, cost));
					graph[(h - 1) * size / 2 + 1].push_back(std::pair<int, long long int>(0, cost));
					DEBUG("[%d <-> %d] = %d\n", 0, (h - 1) * size / 2 + 1, cost);
				}

				else if(w == size - 1 + h % 2)
				{
					graph[size * size + 1].push_back(std::pair<int, long long int>((h - 1) * size / 2 + w, cost));
					graph[(h - 1) * size / 2 + w].push_back(std::pair<int, long long int>(size * size + 1, cost));
					DEBUG("[%d <-> %d] = %d\n", (h - 1) * size / 2 + w, size * size + 1, cost);
				}

				else
				{
					graph[(h - 1) * size / 2 + w].push_back(std::pair<int, long long int>((h - 1) * size / 2 + w + 1, cost));
					graph[(h - 1) * size / 2 + w + 1].push_back(std::pair<int, long long int>((h - 1) * size / 2 + w, cost));
					DEBUG("[%d <-> %d] = %d\n", (h - 1) * size / 2 + w, (h - 1) * size / 2 + w + 1, cost);
				}
			}

			else
			{
				if(h == 0)
				{
					graph[size * size + 1].push_back(std::pair<int, long long int>(w + 1, cost));
					graph[w + 1].push_back(std::pair<int, long long int>(size * size + 1, cost));
					DEBUG("[%d <-> %d] = %d\n", size * size + 1, w + 1, cost);
				}

				else if(h == 2 * size)
				{
					graph[0].push_back(std::pair<int, long long int>((h - 2) * size / 2 + w + 1, cost));
					graph[(h - 2) * size / 2 + w + 1].push_back(std::pair<int, long long int>(0, cost));
					DEBUG("[%d <-> %d] = %d\n", (h - 2) * size / 2 + w + 1, 0, cost);
				}

				else
				{
					graph[(h - 2) * size / 2 + w + 1].push_back(std::pair<int, long long int>(h * size / 2 + w + 1, cost));
					graph[h * size / 2 + w + 1].push_back(std::pair<int, long long int>((h - 2) * size / 2 + w + 1, cost));
					DEBUG("[%d <-> %d] = %d\n", (h - 2) * size / 2 + w + 1, h * size / 2 + w + 1, cost);
				}
			}
		}

	dijkstra();
	printf("%lld\n", distance[size * size + 1]);

	return 0;
}

void dijkstra(void)
{
		for(int v = 0; v <= size * size + 1; ++ v)
			distance[v] = 1000000001;

		que.push(std::pair<long long int, int>(0, 0));

		while(!que.empty())
		{
			act = que.top();
			que.pop();

			if(distance[act.second] < act.first)
				continue;

			distance[act.second] = act.first;
			if(act.second == size * size + 1)
				break;

			for(unsigned int s = 0; s < graph[act.second].size(); ++ s)
				if(distance[graph[act.second][s].first] > act.first + graph[act.second][s].second)
				{
					distance[graph[act.second][s].first] = act.first + graph[act.second][s].second;
					que.push(std::pair<long long int, int>(distance[graph[act.second][s].first], graph[act.second][s].first));
				}
		}
	return;
}
