/* 2011
 * Maciej Szeptuch
 * -*-*-*-*-*-*-*-*-
 */
#include<cstdio>
#include<list>
#include<vector>
//#define DEBUG(args...) fprintf(stderr, args)
#define DEBUG(args...)

const int BUFFER = 4096;
int p = BUFFER - 1;
char buffer[BUFFER];

int getInt(void)
{
	int number = 0;
	while((buffer[p] < '0' || buffer[p] > '9') && ++ p)
		if(p == BUFFER)
		{
			fread(buffer, sizeof(char), BUFFER, stdin);
			p = 0;
		}

	while(buffer[p] >= '0' && buffer[p] <= '9')
	{
		number = number * 10 + buffer[p] - '0';
		++ p;

		if(p == BUFFER)
		{
			fread(buffer, sizeof(char), BUFFER, stdin);
			p = 0;
		}
	}

	return number;
}

int tests,
	height,
	width,
	range,
	map[1024][1024],
	ans[1024][1024];

std::list<std::pair<int, int> > que,
								wque[1024];

int act;

static inline const int MAX(const int &a, const int &b){return a>b?a:b;}

int main(void)
{
	tests = getInt();
	for(int t = 0; t < tests; ++ t)
	{
		height = getInt(); width = getInt(); range = getInt();
		for(int h = 0; h < height; ++ h)
			for(int w = 0; w < width; ++ w)
			{
				map[h][w] = getInt();
				ans[h][w] = 0;
			}

		/* UP */
		for(int w = 0; w < width; ++ w)
			wque[w] = std::list<std::pair<int, int> >();

		for(int h = 0; h < height; ++ h)
		{
			/* ROW SPREAD */
			for(int w = 0; w < width; ++ w)
			{
				act = map[h][w];
				while(!wque[w].empty() && wque[w].front().first < h - range)
					wque[w].pop_front();

				while(!wque[w].empty() && wque[w].back().second <= act)
					wque[w].pop_back();

				wque[w].push_back(std::make_pair(h, act));
			}

			/* LEFT */
			que = std::list<std::pair<int, int> >();
			for(int w = 0; w < width; ++ w)
			{
				act = wque[w].front().second;
				while(!que.empty() && que.front().first < w - range)
					que.pop_front();

				while(!que.empty() && que.back().second <= act)
					que.pop_back();

				que.push_back(std::make_pair(w, act));
				ans[h][w] = MAX(que.front().second, ans[h][w]);
			}

			/* RIGHT */
			que = std::list<std::pair<int, int> >();
			for(int w = width - 1; w >= 0; -- w)
			{
				act = wque[w].front().second;
				while(!que.empty() && que.front().first > w + range)
					que.pop_front();

				while(!que.empty() && que.back().second <= act)
					que.pop_back();

				que.push_back(std::make_pair(w, act));
				ans[h][w] = MAX(que.front().second, ans[h][w]);
			}
		}

		/* DOWN */
		for(int w = 0; w < width; ++ w)
			wque[w] = std::list<std::pair<int, int> >();

		for(int h = height - 1; h >= 0; -- h)
		{
			/* ROW SPREAD */
			for(int w = 0; w < width; ++ w)
			{
				act = map[h][w];
				while(!wque[w].empty() && wque[w].front().first > h + range)
					wque[w].pop_front();

				while(!wque[w].empty() && wque[w].back().second <= act)
					wque[w].pop_back();

				wque[w].push_back(std::make_pair(h, act));
			}

			/* LEFT */
			que = std::list<std::pair<int, int> >();
			for(int w = 0; w < width; ++ w)
			{
				act = wque[w].front().second;
				while(!que.empty() && que.front().first < w - range)
					que.pop_front();

				while(!que.empty() && que.back().second <= act)
					que.pop_back();

				que.push_back(std::make_pair(w, act));
				ans[h][w] = MAX(que.front().second, ans[h][w]);
			}

			/* RIGHT */
			que = std::list<std::pair<int, int> >();
			for(int w = width - 1; w >= 0; -- w)
			{
				act = wque[w].front().second;
				while(!que.empty() && que.front().first > w + range)
					que.pop_front();

				while(!que.empty() && que.back().second <= act)
					que.pop_back();

				que.push_back(std::make_pair(w, act));
				ans[h][w] = MAX(que.front().second, ans[h][w]);
			}
		}

		for(int h = 0; h < height; ++ h)
			for(int w = 0; w < width; ++ w)
				printf("%d%c", ans[h][w], w + 1 == width ? '\n':' ');
	}

	return 0;
}
