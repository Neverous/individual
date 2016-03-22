/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<queue>
#include<vector>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

unsigned int cities,
			 roads,
			 smiths,
			 city,
			 weapons,
			 weapon,
			 from,
			 to,
			 cost[256][256],
			 visited[1 << 13][256],
			 monsters,
			 monster,
			 min (1 << 30);
short int need[256][256],
	  gather[256];
std::vector<unsigned int> graph[256];

static inline void dijkstra(int start);

int main(void)
{
	scanf("%u %u %*u %u", &cities, &roads, &smiths);
	for(unsigned int s = 0; s < smiths; ++ s)
	{
		scanf("%u %u", &city, &weapons);
		-- city;
		for(unsigned int w = 0; w < weapons; ++ w)
		{
			scanf("%u", &weapon);
			-- weapon;
			gather[city] |= (1 << weapon);
		}
	}

	for(unsigned int r = 0; r < roads; ++ r)
	{
		scanf("%u %u", &from, &to);
		-- from;
		-- to;
		graph[from].push_back(to);
		graph[to].push_back(from);
		scanf("%u %u", &cost[from][to], &monsters);
		cost[to][from] = cost[from][to];
		for(unsigned int m = 0; m < monsters; ++ m)
		{
			scanf("%u", &monster);
			-- monster;
			need[from][to] |= (1 << monster);
			need[to][from] |= (1 << monster);
		}
	}

	dijkstra(0);
	for(unsigned int m = 0; m < (1 << 13); ++ m)
		if(min > visited[m][cities - 1])
			min = visited[m][cities - 1];

	printf("%d\n", min == (1 << 30)?-1:(int)min);
	return 0;
}

static inline void dijkstra(int start)
{
	for(unsigned int m = 0; m < (1 << 13); ++ m)
		for(unsigned int s = 0; s < 256; ++ s)
			visited[m][s] = (1 << 30);

	visited[0][start] = 0;
	std::priority_queue<std::pair<std::pair<int, unsigned int>, unsigned int> > que;
	std::pair<std::pair<int, unsigned int>, unsigned int> act;
	unsigned int have;
	que.push(std::make_pair(std::make_pair(0, 0), start));
	while(!que.empty())
	{

		act = que.top();
		que.pop();
		if(-act.first.first != (int)visited[act.first.second][act.second])
			continue;

		//printf("%u: %d %u\n", act.second, -act.first.first, act.first.second);
		have = act.first.second | gather[act.second];
		for(unsigned int n = 0; n < graph[act.second].size(); ++ n)
		{
			if((need[act.second][graph[act.second][n]] & have) != need[act.second][graph[act.second][n]])
				continue; // nie moge jescze przejsc ta krawedzia ;(, za malo broni

			if(visited[have][graph[act.second][n]] <= visited[act.first.second][act.second] + cost[act.second][graph[act.second][n]])
				continue; // juz tam bylem ;]

			visited[have][graph[act.second][n]] = visited[act.first.second][act.second] + cost[act.second][graph[act.second][n]];
			que.push(std::make_pair(std::make_pair(-visited[have][graph[act.second][n]], have), graph[act.second][n]));
		}
	}

	return;
}
