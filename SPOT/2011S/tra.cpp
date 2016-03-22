/* 2011
 * Maciej Szeptuch
 * XIV LO Wrocław
 */
#include<cstdio>
#include<algorithm>
#include<vector>

int tests,
	height,
	width,
	size,
	lifts,
	Sx, Sy,
	Ex, Ey,
	result,
	map[128][128],
	counter[128][128];
std::vector<std::pair<int, int> > graph[128][128];
std::vector<std::pair<int, std::pair<int, int> > > order;

inline static const int DFS(const int &y, const int &x, const int &eY, const int &eX);
inline static const int COUNT(const int &sY, const int &sX, const int &eY, const int &eX);
inline static const int $(const int &a){return a % 1000000007;}

int main(void)
{
	scanf("%d", &tests);
	for(int t = 0; t < tests; ++ t)
	{
		result = 0;
		order.clear();
		scanf("%d %d", &height, &width);
		for(int h = 0; h < height; ++ h)
			for(int w = 0; w < width; ++ w)
			{
				scanf("%d", &size);
				order.push_back(std::make_pair(size, std::make_pair(h, w)));
			}

		std::sort(order.rbegin(), order.rend());
		for(unsigned int o = 0; o < order.size(); ++ o)
			map[order[o].second.first][order[o].second.second] = o;

		scanf("%d", &lifts);
		for(int l = 0; l < lifts; ++ l)
		{
			scanf("%d %d %d %d", &Sy, &Sx, &Ey, &Ex);
			-- Sy; -- Sx;
			-- Ey; -- Ex;

			graph[Sy][Sx].push_back(std::make_pair(Ey, Ex));
		}

		for(int y = 0; y < height; ++ y)
			for(int x = 0; x < width; ++ x)
				result = $(result + DFS(y, x, y, x));

		printf("%d\n", result);
		for(int h = 0; h < height; ++ h)
			for(int w = 0; w < width; ++ w)
				graph[h][w].clear();
	}

	return 0;
}

inline static const int DFS(const int &y, const int &x, const int &eY, const int &eX)
{
	int res = 0;
	if(y != eY || x != eX)
		res = COUNT(y, x, eY, eX);

	for(unsigned int n = 0; n < graph[y][x].size(); ++ n)
		res = $(res + DFS(graph[y][x][n].first, graph[y][x][n].second, eY, eX));

	return res;
}

inline static const int COUNT(const int &sY, const int &sX, const int &eY, const int &eX)
{
	int res,
		x, y, h;
	counter[sY][sX] = 1;
	for(int s = map[sY][sX], e = map[eY][eX]; s <= e; ++ s)
	{
		y = order[s].second.first;
		x = order[s].second.second;
		h = order[s].first;
		for(int i = -1; i < 2; ++ i)
			for(int j = (!i)?-1:0; j < 2; j += 2)
				if(y + i >= 0 && y + i < height && x + j >= 0 && x + j < width)
					if(order[map[y + i][x + j]].first > h)
						counter[y][x] = $(counter[y][x] + counter[y + i][x + j]);
	}

	res = counter[eY][eX];
	for(int s = map[sY][sX], e = map[eY][eX]; s <= e; ++ s)
		counter[order[s].second.first][order[s].second.second] = 0;

	return res;
}
