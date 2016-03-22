/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<vector>
#include<queue>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

int tests,
	size;
char map[1024][1024];
std::queue<std::pair<int, int> > que;
std::pair<int, int> act;

inline static const int solve(void);

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		scanf("%d", &size);
		for(int h = 0; h < size; ++ h)
			scanf("%s", map[h]);

		printf("%d\n", solve());
	}

	return 0;
}

inline static const int solve(void)
{
	int result = size * size;
	que = std::queue<std::pair<int, int> >();
	for(int h = 0; h < size; ++ h)
	{
		if(map[h][0] != '#')
		{
			map[h][0] = '#';
			que.push(std::make_pair(h, 0));
		}

		if(map[h][size - 1] != '#')
		{
			map[h][size - 1] = '#';
			que.push(std::make_pair(h, size - 1));
		}

		if(map[0][h] != '#')
		{
			map[0][h] = '#';
			que.push(std::make_pair(0, h));
		}

		if(map[size - 1][h] != '#')
		{
			map[size - 1][h] = '#';
			que.push(std::make_pair(size - 1, h));
		}
	}

	while(!que.empty())
	{
		act = que.front();
		que.pop();
		-- result;

		for(int x = -1; x < 2; ++ x)
			for(int y = -1; y < 2; ++ y)
				if(act.first + y < size && act.first + y >= 0 && act.second + x < size && act.second + x >= 0 && map[act.first + y][act.second + x] != '#')
				{
					map[act.first + y][act.second + x] = '#';
					que.push(std::make_pair(act.first + y, act.second + x));
				}
	}

	return result;
}
